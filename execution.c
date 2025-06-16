# include "minishell.h"

void	get_file(t_list *list)
{
	t_data *data;

	data = list->begin;
	while (data)
	{
		if (ft_strcmp(data->type, "REDIR_OUT") == 0 || ft_strcmp(data->type, "REDIR_IN") == 0 || ft_strcmp(data->type, "REDIR_OUT_APPEND") == 0)
		{
			if (data->next && ft_strcmp(data->next->type, "ARG") == 0)
				data->next->type = "FILE";
			else if (data->next && ft_strcmp(data->next->type, "SPACE") == 0)
			{
				data = data->next;
				while (data && ft_strcmp(data->type, "SPACE") == 0)
					data = data->next;
				if (ft_strcmp(data->type, "ARG") == 0)
					data->type = "FILE";
			}
		}
		data = data->next;
	}
}

void	exec(t_list *list, char **env, t_global global)
{
	t_data *data = list->begin;
	int	cmds_numb = get_cmd_nb(data);
	int	**pipefd;
	int	status;
	int	i = 0;
	int k;
	pid_t *pid = malloc(sizeof(pid_t) * cmds_numb);

	data = list->begin;
	k = 0;
	pipefd = malloc(sizeof(int *) * cmds_numb);
	while (i < (cmds_numb - 1))
	{
		pipefd[i] = malloc(sizeof(int) * 2);
		pipe(pipefd[i]);
		i++;
	}
	i = 0;
	while (data && i < cmds_numb)
	{
		if (ft_strcmp(data->type, "CMD") == 0)
		{
			pid[i] = fork();
			if (pid[i] < 0)
			{
				perror("fork failed");
				exit(EXIT_FAILURE);
			}
			else if (pid[i] == 0)
			{ 
				search_redir(data);
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
				execve(data->word, data->args, env);
				perror("execve");
				exit(EXIT_FAILURE);
			}
			i++;
		}
		data = data->next;
	}
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
				g_r_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_r_code = WTERMSIG(status) + 128;
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