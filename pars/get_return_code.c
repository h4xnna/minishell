/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_return_code.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:25:53 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/19 17:25:53 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	return_code(t_data *data, char *args)
{
	int		i;
	char	*code;

	i = 0;
	code = ft_itoa(set_get_exit_status(-1));
	if (!code)
		return ;
	while (code[i])
		data->retour[data->j++] = code[i++];
	(void)args;
}

int	check_delim_after_heredoc(t_data *data)
{
	if (ft_strcmp(data->type, "HEREDOC") == 0)
	{
		if (data->next && ft_strcmp(data->next->type, "FILE") == 0)
			return (0);
		printf("bash: syntax error near unexpected token\n");
		return (1);
	}
	return (0);
}

t_list_env	*set_get_env(t_list_env *env)
{
	static t_list_env	*saved_envp;

	if (env == NULL)
		return (saved_envp);
	saved_envp = env;
	return (NULL);
}

void	handle_signel(int sig)
{
	if (sig == SIGINT)
	{
		ft_malloc(-1);
		free_env_list(set_get_env(NULL));
	}
	exit(130);
}
