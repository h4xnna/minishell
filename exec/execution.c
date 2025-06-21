# include "../minishell.h"

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

// void	exec(t_list *list, char **env, t_global global)
// {
// 	t_data	*data = list->begin;
// 	int	cmds_numb = get_cmd_nb(data);
// 	int	**pipefd;
// 	int	status;
// 	int	i = 0;
// 	int k;
// 	pid_t *pid = malloc(sizeof(pid_t) * cmds_numb);
// 	int save_stdout = dup(STDOUT_FILENO);
// 	int save_stdin = dup(STDIN_FILENO);

// 	data = list->begin;
// 	k = 0;
// 	if (cmds_numb > 1)
// 		pipefd = malloc(sizeof(int *) * (cmds_numb - 1));
// 	while (i < (cmds_numb - 1))
// 	{
// 		pipefd[i] = malloc(sizeof(int) * 2);
// 		pipe(pipefd[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (data && i < cmds_numb)
// 	{
// 		signal(SIGINT, SIG_IGN);
// 		is_redir_start(data);
// 		if (ft_strcmp(data->type, "CMD") == 0)
// 		{
// 			pid[i] = fork();
// 			if (pid[i] < 0)
// 			{
// 				perror("fork failed");
// 				exit(EXIT_FAILURE);
// 			}
// 			else if (pid[i] == 0)
// 			{ 
// 				signal(SIGINT, SIG_DFL);
// 				search_redir(data);
// 				if (!is_redir_out(data) && cmds_numb > 1)
// 				{
// 					if (i == 0)
// 						ft_first_cmd(pipefd, i);
// 					else if (i == cmds_numb - 1)
// 						ft_last_cmd(pipefd, i); 
// 					else
// 						ft_middle_cmd(pipefd, i);
// 					ft_close_all_pipes(pipefd, data, list);
// 				}
// 				execve(data->word, data->args, env);
// 				perror("execve");
// 				exit(EXIT_FAILURE);
// 			}
// 			i++;
// 		}
// 		data = data->next;
// 	}
// 	dup2(save_stdout, STDOUT_FILENO);
// 	dup2(save_stdin, STDIN_FILENO);
// 	close(save_stdin);
// 	close(save_stdout);
// 	if (cmds_numb > 1) 
// 	{
// 		ft_close_all_pipes(pipefd, data, list);
// 	}
// 	while (k < cmds_numb)
// 	{
// 		if (waitpid(pid[k], &status, 0) == -1)
// 		{
// 			perror("waitpid");
// 			return ;
// 		}
// 		if (k == cmds_numb - 1)
// 		{
// 			if (WIFEXITED(status))
// 				g_r_code = WEXITSTATUS(status);
// 			else if (WIFSIGNALED(status))
// 			{
// 				if (WTERMSIG(status) == SIGINT)
// 				{
// 					write(1, "\n", 1);
// 					g_r_code = WTERMSIG(status) + 128;
// 				}
// 				if (WTERMSIG(status) == SIGQUIT)
// 				{
// 					write(1, "\n", 1);
// 					g_r_code = WTERMSIG(status) + 128;
// 				}
// 			}
				
// 		}
// 		k++;
// 	}
// 	if (cmds_numb > 1) 
// 	{
// 		i = 0;
// 		while (i < cmds_numb - 1) 
// 			free(pipefd[i++]);
// 		free(pipefd);
// 	}
// 	free(pid);
// }

void	child_process(t_pipex *pipex, int i, char **av, char **envp,  t_data *data )
{
	if (i == 0)
		dup2(pipex->infilefd, 0);
	else
		dup2(pipex->pipefd[i - 1][0], 0);
	if (i == (pipex->count_cmd - 1))
		dup2(pipex->outfilefd, 1);
	else
		dup2(pipex->pipefd[i][1], 1);
	close_pipes(pipex);
	(void)av;
	execve(data->word, data->args, envp);
}

int run_pipex(int ac, char **av, char **envp, t_data *data)
{
    t_pipex *pipex;
    int i;

    i = 0;
    if (ac >= 4)
    {
        pipex = init_pipex(ac, av);
        if (!pipex)
            return (1);
        while (pipex->count_cmd > i)
        {
            pipex->pid[i] = fork();
            if (pipex->pid[i] < 0)
                return (1);
            if (pipex->pid[i] == 0) 
                child_process(pipex, i, av, envp, data);
            i++;
        }
        close(pipex->infilefd);
        close(pipex->outfilefd);
        close_pipes(pipex);
        i = 0;
        while (i < pipex->count_cmd)
        {
            waitpid(pipex->pid[i], NULL, 0);
            i++;
        }
        free(pipex->pid);
        free(pipex->pipefd);
        free(pipex);
        return (0);
    }
    return (1);
}

