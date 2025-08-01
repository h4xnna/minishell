/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:54:54 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/19 08:54:54 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	space_pars(t_list *list, t_data *data)
{
	if (data->j > 0)
	{
		data->retour[data->j] = '\0';
		node_creation(list, data->retour);
		data->j = 0;
	}
	data->i++;
}

void	operator_pars(t_list *list, t_data *data, char *args)
{
	if (data->j > 0)
	{
		data->retour[data->j] = '\0';
		node_creation(list, data->retour);
		data->j = 0;
	}
	if (args[data->i] == '>' && args[data->i + 1] == '>')
	{
		node_creation(list, ">>");
		data->i += 2;
	}
	else if (args[data->i] == '<' && args[data->i + 1] == '<')
	{
		node_creation(list, "<<");
		data->i += 2;
	}
	else
	{
		data->retour[0] = args[data->i++];
		data->retour[1] = '\0';
		node_creation(list, data->retour);
	}
}

void	single_quote_pars(t_data *data, char *args)
{
	data->i++;
	while (args[data->i] && args[data->i] != '\'')
		data->retour[data->j++] = args[data->i++];
	if (args[data->i == 1] == '\'')
		data->retour[data->j++] = ' ';
	if (args[data->i] == '\'')
		data->i++;
	else
		return ;
}

void	double_quotes_pars(t_data *data, char *args)
{
	data->i++;
	while (args[data->i] && args[data->i] != '"')
	{
		if (args[data->i] == '$')
			double_quotes_expansion(data, args);
		else
			data->retour[data->j++] = args[data->i++];
	}
	if (args[data->i == 1] == '"')
		data->retour[data->j++] = ' ';
	if (args[data->i] == '"')
		data->i++;
	else
		return ;
}
