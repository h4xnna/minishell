/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:41:42 by hmimouni          #+#    #+#             */
/*   Updated: 2025/07/24 19:02:09 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_in_env(char *expand, t_list_env *env)
{
	char	*out;
	t_env	*tmp;

	tmp = env->begin;
	while (tmp) 
	{
		if (ft_strcmp(expand, tmp->key) == 0)
		{
			out = tmp->value;
			return (out);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
