/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_hanling_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:29:29 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/19 17:29:29 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_pars_digit_quote(t_data *data, char *args)
{
	char	c;

	c = args[data->i];
	data->i++;
	if (is_quote(args[data->i - 1]))
	{
		while (args[data->i] && !is_quote(args[data->i]))
			data->retour[data->j++] = args[data->i++];
		if (args[data->i] == c)
			data->i++;
		else
			exit (1);
	}
	while (is_digit(args[data->i]))
		data->i++;
}

void	dollar_pars(t_data *data, char *args, t_global global)
{
	data->i++;
	if (is_digit(args[data->i]) || is_quote(args[data->i]))
	{
		dollar_pars_digit_quote(data, args);
	}
	else if (args[data->i] == '=' || args[data->i] == '%')
		data->retour[data->j++] = '$';
	else if (args[data->i] == '?')
	{
		return_code(data, args, global);
		data->i++;
	}
	else
		expansion(data, args);
}
