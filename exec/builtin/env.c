/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 21:26:01 by hmimouni          #+#    #+#             */
/*   Updated: 2025/06/24 22:12:33 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_env( t_list_env *envp)
{
	while (envp->begin != envp->end)
	{
		printf("%s : %s\n", envp->begin->key, envp->begin->value);
		envp->begin = envp->begin->next;
	}

	exit(0);
}