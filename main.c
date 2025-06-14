# include "minishell.h"

void	print_list(t_list *list)
{
	t_data *data;
	int	i;
	int j;

	data = list->begin;
	// while (data)
	// {
	// 	i = 0;
	// 	if (ft_strcmp(data->type, "CMD") == 0)
	// 	{
	// 		while (data->args[i] != NULL)
	// 		{
	// 			j = 0;
	// 			while (data->args[i][j])
	// 			{
	// 				printf("%c", data->args[i][j]);
	// 				j++;
	// 			}
	// 			printf("\n");
	// 			i++;
	// 		}
	// 	}
	// 	data = data->next;
	// }
	while (data)
	{
		printf("%s\n", data->type);
		printf("%s\n", data->word);
		data = data->next;
	}
}

void	free_list(t_list *list)
{
	t_data	*data;
	t_data	*temp;

	data = list->begin;
	if (!list)
		return ;
	while (data)
	{
		temp = data;
		data = data->next;
		free(temp);
	}
	list->begin = NULL;
	free(list);
}

void	get_type(t_data *data, t_list *list)
{
	data = list->begin;
	while (data)
	{
		if (is_cmd(data->word, data))
			data->type = "CMD";
		else if (ft_strcmp(data->word, ">") == 0)
			data->type = "REDIR_OUT";
		else if (ft_strcmp(data->word, "<") == 0)
			data->type = "REDIR_IN";
		else if (ft_strcmp(data->word, ">>") == 0)
			data->type = "REDIR_OUT_2";
		else if (ft_strcmp(data->word, "<<") == 0)
			data->type = "HEREDOC";
		else if (ft_strcmp(data->word, "\0") == 0)
			data->type = "SPACE";
		else if (ft_strcmp(data->word, "|") == 0)
			data->type = "PIPE";
		else
			data->type = "ARG";
		data = data->next;
	}
}

void	return_code(t_data *data, char *args)
{
	int	i;
	char *code;

	i = 0;
	if (data->index == 1)
		data->retour[data->j++] = '0';
	else
	{
		code = ft_itoa(data->rcode);
		while (code[i])
			data->retour[data->j++] = code[i++];
		free(code);
	}
}

int	main(int ac, char **av, char **env)
{
	t_list *list;
	t_data	*data;
	char *args;

	data = malloc(sizeof(t_data));
	list = malloc(sizeof(t_list));
	if (!list ||!data)
		return (0);
	list->begin = NULL;
	list->end = NULL;
	while (1)
	{
		if (list->begin)
			data = list->begin;
		args = readline("Minishell > ");
		add_history(args);
		initialisation(data, args, env);
		data->index++;
		get_word(list, args, data);
		get_type(data, list);
		get_args_cmd(data, list);
		get_file(list);
		// print_list(list);
		exec(list, env);
		rl_redisplay();
		free_list(list);
	}
	return (0);
}