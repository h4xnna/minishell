/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 19:44:03 by hmimouni          #+#    #+#             */
/*   Updated: 2025/07/14 18:49:20 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_get_exit_status(int exit_code)
{
	static int	exit_status;

	if (exit_code == -1)
		return (exit_status);
	exit_status = exit_code;
	return (0);
}

void	print_splash_screen(void)
{
	printf("\033[38;5;129m\n");
	printf("%s\n",
		"███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     ");
	printf("%s\n",
		"████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     ");
	printf("%s\n",
		"██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     ");
	printf("%s\n",
		"██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     ");
	printf("%s\n",
		"██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗");
	printf("%s\n",
		"╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝");
	printf("\033[0m\n");
}

void	test_builtins_child(t_data *data, t_list_env *envp)
{
	(void)envp;
	if (ft_strcmp(data->word, "echo") == 0)
		ft_echo(data->args);
	else if (ft_strcmp(data->word, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(data->word, "env") == 0)
		ft_env(envp, data);
}

void	test_builtins_parents(t_data *data, t_list_env *env)
{
	if (ft_strcmp(data->word, "exit") == 0)
		ft_exit(data->args);
	else if (ft_strcmp(data->word, "cd") == 0)
		ft_cd(data->args, env);
	else if (ft_strcmp(data->word, "unset") == 0)
		ft_unset(env, data->args);
	else if (ft_strcmp(data->word, "export") == 0)
		ft_export(env, data->args);
}
// int main(void)
// {
// 	code = ft_itoa(set_get_exit_status(-1));

// 	int exit_code;

// 	exit_code = set_get_exit_status(-1);

// 	printf("EXIT CODE : [%d]\n", exit_code);
// 	printf("EXIT CODE : [%d]\n", set_get_exit_status(-1));

// 	set_get_exit_status(130);

// 	exit_code = set_get_exit_status(-1);

// 	printf("\n");
// 	printf("EXIT CODE : [%d]\n", exit_code);
// 	printf("EXIT CODE : [%d]\n", set_get_exit_status(-1));
// }