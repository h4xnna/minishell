/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:10:08 by hmimouni          #+#    #+#             */
/*   Updated: 2025/06/27 18:01:58 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	find_and_remove(t_list_env *envp, char *key)
{
	t_env	*tmp;
	t_env	*delete;

	tmp = envp->begin;
	while (tmp)
	{
		if (strcmp(tmp->key, key) == 0)
		{
			delete = tmp;
			if (tmp->back)
				tmp->back->next = tmp->next;
			else
				tmp = tmp->next;
			if (tmp->next)
				tmp->next->back = tmp->back;
			else
				envp->end = tmp->back;
			free(delete->key);
			free(delete->value);
			free(delete);
			return ;
		}
		else
			tmp = tmp->next;
	}
}

void	ft_unset(t_list_env *envp, char **args)
{
	int	i;

	i = 1;
	if (!args[i] || !args)
		return ;
	while (args[i])
	{
		find_and_remove(envp, args[i]);
		i++;
	}
}
