/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:54:56 by acrusoe           #+#    #+#             */
/*   Updated: 2025/07/16 15:54:56 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_creation(t_data *data, int cmds_numb)
{
	int	i;

	i = 0;
	if (cmds_numb > 1)
		data->pipefd = malloc(sizeof(int *) * (cmds_numb - 1));
	while (i < (cmds_numb - 1))
	{
		data->pipefd[i] = malloc(sizeof(int) * 2);
		pipe(data->pipefd[i]);
		i++;
	}
}

void	child_process_pipe(t_data *data, t_list *list,
	t_list_env *env_list, int i)
{
	int	cmds_numb;

	cmds_numb = get_cmd_nb(data, list);
	signal(SIGINT, SIG_DFL);
	search_redir(data, env_list);
	if (!is_redir_out(data) && cmds_numb > 1)
	{
		if (i == 0)
			ft_first_cmd(list->begin->pipefd, i);
		else if (i == cmds_numb - 1)
			ft_last_cmd(list->begin->pipefd, i);
		else
			ft_middle_cmd(list->begin->pipefd, i);
		ft_close_all_pipes(list->begin->pipefd, data, list);
	}
	if (built_cmd_child(data->word))
		test_builtins_child(data, env_list);
	else
		execve(data->word, data->args, data->env_child_process);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	last_pid_handler(int status)
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

void	pids_handler(pid_t *pid, int cmds_numb)
{
	int	status;
	int	k;

	k = 0;
	while (k < cmds_numb)
	{
		if (waitpid(pid[k], &status, 0) == -1)
		{
			perror("waitpid");
			return ;
		}
		if (k == cmds_numb - 1)
			last_pid_handler(status);
		k++;
	}
}
