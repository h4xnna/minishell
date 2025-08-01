void	ft_first_cmd(int **pipefd, int i)
{
	dup2(pipefd[i][1], STDOUT_FILENO);
	close(pipefd[i][1]);
}

void	ft_middle_cmd(int **pipefd, int i)
{
	dup2(pipefd[i - 1][0], STDIN_FILENO);
	dup2(pipefd[i][1], STDOUT_FILENO);
	close(pipefd[i][1]);
	close(pipefd[i - 1][0]);
}

void	ft_last_cmd(int **pipefd, int i)
{
	dup2(pipefd[i - 1][0], STDIN_FILENO);
	close(pipefd[i - 1][0]);
}

void	ft_close_all_pipes(int **pipefd, t_data *data, t_list *list)
{
	int	i;
	int	j;

	i = 0;
	data = list->begin;
	j = get_cmd_nb(data, list);
	while (i < (j - 1))
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
}
int	is_redir_out(t_data *data)
{
	if (ft_strcmp(data->type, "REDIR_OUT") == 0)
		return (1);
	return (0);
}

int	is_redir_out2(t_data *data)
{
	if (ft_strcmp(data->type, "REDIR_OUT") == 0)
		return (1);
	return (0);
}

void	ft_redir_out(t_data *data)
{
	int	fd_outfile;

	if (data->next && ft_strcmp(data->next->type, "FILE") == 0)
	{
		fd_outfile = open(data->next->word, O_CREAT | O_WRONLY
				| O_TRUNC, S_IRUSR | S_IWUSR);
		if (fd_outfile < 0)
		{
			perror("open failed");
			exit(EXIT_FAILURE);
		}
		dup2(fd_outfile, STDOUT_FILENO);
		close(fd_outfile);
	}
}

int	is_redir_out_append(t_data *data)
{
	if (ft_strcmp(data->type, "REDIR_OUT_APPEND") == 0)
		return (1);
	return (0);
}

void	ft_redir_out_append(t_data *data)
{
	int	fd_outfile;

	if (data->next && ft_strcmp(data->next->type, "FILE") == 0)
	{
		fd_outfile = open(data->next->word, O_CREAT | O_WRONLY
				| O_APPEND, S_IRUSR | S_IWUSR);
		if (fd_outfile < 0)
		{
			perror("open failed");
			exit(EXIT_FAILURE);
		}
		dup2(fd_outfile, STDOUT_FILENO);
		close(fd_outfile);
	}
}



int	search_redir(t_data *data, t_list_env *env, t_list *list)
{
	is_redir_start(data, env, list);
	while (data && ft_strcmp(data->type, "PIPE"))
	{
		if (is_redir_in(data))
			ft_redir_in(data);
		else if (has_heredoc(data))
		{
			if (!here_doc(data, env))
				return (0);
		}
		else if (is_redir_out(data))
			ft_redir_out(data);
		else if (is_redir_out_append(data))
			ft_redir_out_append(data);
		data = data->next;
	}
	return (1);
}

int	is_redir_start(t_data *data, t_list_env *env, t_list *list)
{
	data = list->begin;
	if (ft_strcmp(data->type, "REDIR_IN") == 0)
		ft_redir_in(data);
	else if (ft_strcmp(data->type, "REDIR_OUT") == 0)
		ft_redir_out(data);
	else if (ft_strcmp(data->type, "REDIR_OUT_APPEND") == 0)
		ft_redir_out_append(data);
	else if (ft_strcmp(data->type, "HERE_DOC") == 0)
	{
		if (!here_doc(data, env))
			return (0);
	}
	return (1);
}



int	child_process_pipe(t_data *data, t_list *list,
						t_list_env *env_list, int i)
{
	int	cmds_numb;
	
	cmds_numb = get_cmd_nb(data, list);
	signal(SIGINT, SIG_DFL);
	if (cmds_numb > 1)
		check_pipes(i, data, list, cmds_numb);
	if (!search_redir(data, env_list, list))
		exit(0);
	if (built_cmd_child(data->word))
		test_builtins_child(data, env_list, list);
	else
		execve(data->word, data->args, data->env_child_process);
	perror("execve");
	exit(EXIT_FAILURE);
	return (1);
}


int	exec_main_function(t_data *data, t_list *list,
					t_list_env *env_list, pid_t *pid)
{
	int original_stdout;

	original_stdout = dup(STDOUT_FILENO);
	while (data && list->begin->ind < list->begin->cmds_numb)
	{
		signal(SIGINT, SIG_IGN);
		// if (!is_redir_start(data, env_list))
		// 	return (handle_heredoc_failure(data));
		if (ft_strcmp(data->type, "CMD") == 0)
		{
			dup2(original_stdout, STDOUT_FILENO);
			close(original_stdout);
			if (handle_builtin_if_needed(data, env_list, list))
				return (1);
			if (!handle_fork_and_exec(data, list, env_list, pid))
				break ;
		}
		data = data->next;
	}
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
	return (0);
}