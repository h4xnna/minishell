/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:38:35 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/19 08:38:35 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exec(t_list *list, char *args, char **env, t_list_env *env_list)
{
	t_data	*data;

	data = list->begin;
	while (data)
	{
		if (ft_strcmp(data->type, "CMD") == 0)
		{
			exec(list, env, env_list);
			data->here_doc_fd = 0;
			return ;
		}
		data = data->next;
	} 
	if (list->begin && ft_strcmp(list->begin->type, "HERE_DOC") == 0)
	{
		data = list->begin;
		here_doc(data);
	}
	if (!data)
		print_error(list, args);
}

int	is_unclosed_quotes(char *args)
{
	int	i;
	int	count;
	int	count2;

	i = 0;
	count = 0;
	count2 = 0;
	while (args[i])
	{
		if (args[i] == '\'')
			count += 1;
		if (args[i] == '\"')
			count2 += 1;
		if (count == 2)
			count = 0;
		if (count2 == 2)
			count2 = 0;
		i++;
	}
	if (count != 0 || count2 != 0)
		return (1);
	return (0);
}

void	tokenisation_and_exec(t_list *list, char *args, char **env, t_list_env *env_list)
{
	t_data	*data;

	data = list->begin;
	get_type(data, list, env_list);
	get_file(list);
	if (wrong_token_error(data, list))
	{
		free_list(list);
		free(args);
		signal_handlers();
		return ;
	}
	get_args_cmd(data, list);
	print_exec(list, args, env, env_list);
	rl_redisplay();
	signal_handlers();
}

void	program_handler(t_list *list, char *args, t_global global, char **env, t_list_env *env_list)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	ft_memset(data, 0, sizeof(t_data));
	initialisation(data, args);
	if (is_unclosed_quotes(args))
	{
		free_list(list);
		signal_handlers();
		set_get_exit_status(0);
		return ;
	}
	get_word(list, args, data, global);
	tokenisation_and_exec(list, args, env, env_list);
	free_list(list);
	free(args);
}

void	initialisation_list(t_list **list)
{
	*list = malloc(sizeof(t_list));
	if (!*list)
		return ;
	(*list)->begin = NULL;
	(*list)->end = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_global	global;
	t_list		*list;
	char		*args;

	global.index = 0;
	(void)av;
	(void)ac;
	print_splash_screen();
	signal_handlers();
	t_list_env	*env_list;

	env_list = malloc(sizeof(t_list_env));
	if (!env_list)
		return (1);
	(env_list)->begin = NULL;
	(env_list)->end = NULL;
	get_env_key(env, env_list);
	env_value(env_list, env);
	while (1)
	{
		initialisation_list(&list);
		args = readline("\033[1m\033[38;5;129mMinishell → \033[0m");
		if (!args)
		{
			free_list(list);
			write(1, "exit\n", 5);
			break ;
		}
		add_history(args);
		global.index++;
		program_handler(list, args, global, env, env_list);
	}
	free_env_list(env_list);
	return (0);
}
