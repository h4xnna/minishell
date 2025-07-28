/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 19:44:03 by hmimouni          #+#    #+#             */
/*   Updated: 2025/07/28 23:52:28 by hmimouni         ###   ########.fr       */
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
	if (ft_strcmp(data->word, "echo") == 0)
		ft_echo(data->args);
	else if (ft_strcmp(data->word, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(data->word, "env") == 0)
		ft_env(envp, data);
	else if (ft_strcmp(data->word, "cd") == 0)
		ft_cd(data->args, envp);
	else if (ft_strcmp(data->word, "unset") == 0)
		ft_unset(envp, data->args);
	else if (ft_strcmp(data->word, "export") == 0)
		ft_export(envp, data->args);
	free_env_list(envp);
	ft_malloc(-1);
	exit(0);
}

void	test_builtins_parents(t_data *data, t_list_env *env)
{
	close(data->saved_stdin);
	if (ft_strcmp(data->word, "exit") == 0)
		ft_exit(data->args);
	(void)data;
	(void)env;
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