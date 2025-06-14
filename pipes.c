# include "minishell.h"

int	get_cmd_nb(t_data *data)
{
	int cmds_numb;

	cmds_numb = 0;
	while (data)
	{
		if (ft_strcmp(data->type, "CMD") == 0)
			cmds_numb++;
		data = data->next;
	}
	return (cmds_numb);
}

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

void    ft_close_all_pipes(int **pipefd, t_data *data, t_list *list)
{
	int i;
	int j;

	i = 0;
	data = list->begin;
	j = get_cmd_nb(data);
	while (i < (j - 1))
	{
		close(pipefd[i][0]); 
		close(pipefd[i][1]); 
		i++;
	}
}