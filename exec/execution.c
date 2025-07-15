/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/07/01 20:06:03 by hmimouni          #+#    #+#             */
/*   Updated: 2025/07/01 20:06:03 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	is_redirections(t_data *data)
{
	if (ft_strcmp(data->type, "REDIR_OUT") == 0)
		return (1);
	if (ft_strcmp(data->type, "REDIR_IN") == 0)
		return (1);
	if (ft_strcmp(data->type, "REDIR_OUT_APPEND") == 0)
		return (1);
	return (0);
}

void	get_file(t_list *list)
{
	t_data *data;

	data = list->begin;
	while (data)
	{
		if (is_redirections(data))
		{
			if (data->next)
				data->next->type = "FILE";
		}
		data = data->next;
	}
}

void	exec(t_list *list, char **env, t_list_env *env_list)
{
	t_data *data = list->begin;
	int cmds_numb = get_cmd_nb(data);
	int **pipefd;
	int status;
	int i = 0;
	int k;
	pid_t *pid = malloc(sizeof(pid_t) * cmds_numb);
	int save_stdout = dup(STDOUT_FILENO);
	int save_stdin = dup(STDIN_FILENO);

	data = list->begin;
	k = 0;
	if (cmds_numb > 1)
		pipefd = malloc(sizeof(int *) * (cmds_numb - 1));
	while (i < (cmds_numb - 1))
	{
		pipefd[i] = malloc(sizeof(int) * 2);
		pipe(pipefd[i]);
		i++;
	}
	i = 0;
	while (data && i < cmds_numb)
	{
		signal(SIGINT, SIG_IGN);
		is_redir_start(data, env_list);
		if (ft_strcmp(data->type, "CMD") == 0)
		{
			if (built_cmd_parent(data->word))
			{
				test_builtins_parents(data, env_list);
				return ;
			}
			pid[i] = fork();
			if (pid[i] < 0)
			{
				perror("fork failed");
				exit(EXIT_FAILURE);
			}
			else if (pid[i] == 0)
			{
				signal(SIGINT, SIG_DFL);
				search_redir(data, env_list);
				if (!is_redir_out(data) && cmds_numb > 1)
				{
					if (i == 0)
						ft_first_cmd(pipefd, i);
					else if (i == cmds_numb - 1)
						ft_last_cmd(pipefd, i);
					else
						ft_middle_cmd(pipefd, i);
					ft_close_all_pipes(pipefd, data, list);
				}
				if (built_cmd_child(data->word))
					test_builtins_child(data, env_list);
				else
					execve(data->word, data->args, env);
				perror("execve");
				exit(EXIT_FAILURE);
			}
			i++;
		}
		data = data->next;
	}
	dup2(save_stdin, STDIN_FILENO);
	close(save_stdin);
	close(save_stdout);
	if (cmds_numb > 1)
	{
		ft_close_all_pipes(pipefd, data, list);
	}
	while (k < cmds_numb)
	{
		if (waitpid(pid[k], &status, 0) == -1)
		{
			perror("waitpid");
			return ;
		}
		if (k == cmds_numb - 1)
		{
			if (WIFEXITED(status))
				set_get_exit_status(WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
				{
					write(1, "\n", 1);
					set_get_exit_status(WTERMSIG(status) + 128);
				}
				if (WTERMSIG(status) == SIGQUIT)
				{
					write(1, "\n", 1);
					set_get_exit_status(WTERMSIG(status) + 128);
				}
			}
		}
		k++;
	}
	if (cmds_numb > 1)
	{
		i = 0;
		while (i < cmds_numb - 1)
			free(pipefd[i++]);
		free(pipefd);
	}
	free(pid);
}
