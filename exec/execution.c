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
	t_data	*data;

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

void	exec_main_function(t_data *data, t_list *list, t_list_env *env_list,
	pid_t *pid)
{
	while (data && list->begin->ind < list->begin->cmds_numb)
	{
		signal(SIGINT, SIG_IGN);
		if (!is_redir_start(data, env_list))
		{
			data->heredoc_exit = 1;
			return ;
		}
		if (ft_strcmp(data->type, "CMD") == 0)
		{
			if (built_cmd_parent(data->word))
			{
				test_builtins_parents(data, env_list);
				return ;
			}
			pid[list->begin->ind] = fork();
			if (pid[list->begin->ind] < 0)
			{
				perror("fork failed");
				exit(EXIT_FAILURE);
			}
			else if (pid[list->begin->ind] == 0)
			{
				if (!child_process_pipe(data, list, env_list, list->begin->ind))
				{
					data->heredoc_exit = 1;
					break;
				}
			}
			list->begin->ind++;
		}
		data = data->next;
	}
}

void	exec(t_list *list, t_list_env *env_list)
{
	t_data	*data;
	int		cmds_numb;
	pid_t	*pid;

	data = NULL;
	cmds_numb = get_cmd_nb(data, list);
	pid = malloc(sizeof(pid_t) * cmds_numb);
	data = list->begin;
	pipe_creation(data, cmds_numb);
	exec_main_function(data, list, env_list, pid);
	// signal(SIGINT, SIG_DFL);
	if (cmds_numb > 1)
		ft_close_all_pipes(list->begin->pipefd, data, list);
	if (!data->heredoc_exit)
		pids_handler(pid, cmds_numb);
	free_pipes_and_pid(cmds_numb, list, pid);
}
