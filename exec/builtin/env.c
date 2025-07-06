/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 21:26:01 by hmimouni          #+#    #+#             */
/*   Updated: 2025/07/05 20:46:55 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_list_env *envp, t_data *data)
{
	if(data->next)
		exit(0);
	while (envp->begin)
	{
		printf("%s=%s\n", envp->begin->key, envp->begin->value);
		envp->begin = envp->begin->next;
	}

	exit(0);
}