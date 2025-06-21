/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:23:45 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/19 17:23:45 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_token_type(t_data *data, int *cmd_nb)
{
	if (*cmd_nb == 0 && is_cmd(data->word, data))
	{
		(*cmd_nb)++;
		return ("CMD");
	}
	else if (ft_strcmp(data->word, ">") == 0)
		return ("REDIR_OUT");
	else if (ft_strcmp(data->word, ">>") == 0)
		return ("REDIR_OUT_APPEND");
	else if (ft_strcmp(data->word, "<") == 0)
		return ("REDIR_IN");
	else if (ft_strcmp(data->word, "<<") == 0)
		return ("REDIR_IN");
	else if (ft_strcmp(data->word, "|") == 0)
	{
		*cmd_nb = 0;
		return ("PIPE");
	}
	else
		return ("ARG");
}

void	get_type(t_data *data, t_list *list)
{
	int	cmd_nb;

	cmd_nb = 0;
	data = list->begin;
	while (data)
	{
		data->type = get_token_type(data, &cmd_nb);
		data = data->next;
	}
}
