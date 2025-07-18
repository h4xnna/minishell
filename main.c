/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/06/19 08:38:35 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/19 08:38:35 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exec(t_list *list, char *args, t_list_env *env_list)
{
	t_data	*data;
	int saved_stdin = dup(STDIN_FILENO); 

	data = list->begin;
	while (data)
	{
		if (ft_strcmp(data->type, "CMD") == 0)
		{
			exec(list, env_list);
			if (data->here_doc_fd > 0)
				unlink("here_doc");
			data->here_doc_fd = 0;
			dup2(saved_stdin, STDIN_FILENO);
			return ;
		}
		data = data->next;
	}
	if (list->begin && ft_strcmp(list->begin->type, "HERE_DOC") == 0)
	{
		data = list->begin;
		here_doc(data, env_list);
		dup2(saved_stdin, STDIN_FILENO);
	}
	if (!data)
		print_error(list, args);
}

int	tokenisation_and_exec(t_list *list, char *args,
		t_list_env *env_list)
{
	t_data	*data;

	data = list->begin;
	get_type(data, list, env_list);
	get_file(list);
	if (wrong_token_error(data, list))
		return (0);
	get_args_cmd(data, list);
	initialisation_cmd_numb(data, list);
	print_exec(list, args, env_list);
	rl_redisplay();
	signal_handlers();
	return (1);
}

void	program_handler(t_list *list, char *args, char **env,
		t_list_env *env_list)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	ft_memset(data, 0, sizeof(t_data));
	initialisation(data, args, env);
	if (is_unclosed_quotes(args))
	{
		free_list(list);
		signal_handlers();
		set_get_exit_status(0);
		return ;
	}
	get_word(list, args, data);
	if (!tokenisation_and_exec(list, args, env_list))
	{
		free_list(list);
		free(args);
		signal_handlers();
		return ;
	}
	if (list)
		free_list(list);
	free(args);
}

void	main_loop_function(t_list *list, char *args, char **env,
	t_list_env *env_list)
{
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
		flag++;
		program_handler(list, args, env, env_list);
	}
}

int	main(int ac, char **av, char **env)
{
	t_list		*list;
	char		*args;
	t_list_env	*env_list;

	(void)av;
	(void)ac;
	flag = 0;
	args = NULL;
	list = NULL;
	print_splash_screen();
	signal_handlers();
	initialisation_env_list(&env_list);
	get_env_key(env, env_list);
	env_value(env_list, env);
	main_loop_function(list, args, env, env_list);
	free_env_list(env_list);
	return (0);
}
