/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_checker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:10:04 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/19 17:10:04 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	search_redir(t_data *data, t_list_env *env)
{
	while (data && ft_strcmp(data->type, "PIPE"))
	{
		if (is_redir_in(data))
			ft_redir_in(data);
		else if (has_heredoc(data))
		{
			if (!here_doc(data, env))
				return (0);
		}
		else if (is_redir_out(data))
			ft_redir_out(data);
		else if (is_redir_out_append(data))
			ft_redir_out_append(data);
		data = data->next;
	}
	return (1);
}

// int	is_redir_start(t_data *data, t_list_env *env, t_list *list)
// {
// 	data = list->begin;
// 	if (ft_strcmp(data->type, "REDIR_IN") == 0)
// 		ft_redir_in(data);
// 	else if (ft_strcmp(data->type, "REDIR_OUT") == 0)
// 		ft_redir_out(data);
// 	else if (ft_strcmp(data->type, "REDIR_OUT_APPEND") == 0)
// 		ft_redir_out_append(data);
// 	else if (ft_strcmp(data->type, "HERE_DOC") == 0)
// 	{
// 		if (!here_doc(data, env))
// 			return (0);
// 	}
// 	return (1);
// }

int	search_redir_backward(t_data *data, t_list_env *env)
{
	// if (list->begin->redir_check == 0)
	// 	is_redir_start(data, env, list);
	while (data && ft_strcmp(data->type, "PIPE"))
	{
		if (is_redir_in(data))
			ft_redir_in(data);
		else if (has_heredoc(data))
		{
			if (!here_doc(data, env))
				return (0);
		}
		else if (is_redir_out(data))
			ft_redir_out(data);
		else if (is_redir_out_append(data))
			ft_redir_out_append(data);
		data = data->back;
	}
	return (1);
}