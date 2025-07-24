/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax error token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:15:33 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/19 17:15:33 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_file_after_redirin(t_data *data)
{
	struct stat	sb;

	if (ft_strcmp(data->type, "REDIR_IN") == 0)
	{
		if (data->next && ft_strcmp(data->next->type, "FILE") == 0)
		{
			if (stat(data->next->word, &sb) != 0
				&& !S_ISREG(sb.st_mode)
				&& (access(data->next->word, R_OK) != 0))
			{
				printf("bash: %s: No such file or directory \n",
					data->next->word);
				return (1);
			}
			return (0);
		}
		printf("bash: syntax error near unexpected token\n");
		return (1);
	}
	return (0);
}

int	check_file_after_redirout(t_data *data)
{
	if (is_redir_out(data) || is_redir_out_append(data))
	{
		if (data->next && ft_strcmp(data->next->type, "FILE") == 0)
			return (0);
		printf("bash: syntax error near unexpected token\n");
		return (1);
	}
	return (0);
}

int	last_pipe_not_followed_by_cmd(t_data *data)
{
	int	flag;

	while (data)
	{
		flag = 0;
		if (data->next && ft_strcmp(data->type, "PIPE") == 0)
		{
			if (ft_strcmp(data->next->type, "CMD") == 0)
				flag = 1;
			data = data->next;
		}
		else
			flag = 1;
		data = data->next;
	}
	if (flag == 0)
	{
		printf("bash: command not found\n");
		return (0);
	}
	return (1);
}

void	pipe_not_followed_by_cmd(t_data *data)
{
	int flag;

	flag = 0;
	while (data->next != NULL)
	{
		if (ft_strcmp(data->type, "CMD") == 0)
			flag = 1;
		if (ft_strcmp(data->type, "PIPE") == 0)
		{
			if (flag == 0)
				printf("bash: command not found\n");
			else
				flag = 0;
		}
		data = data->next;
	}
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

int	wrong_token_error(t_data *data, t_list *list)
{
	if (!list->begin)
		return (0);
	data = list->begin;
	if (ft_strcmp(list->begin->type, "PIPE") == 0)
	{
		printf("bash: syntax error near unexpected token\n");
		return (1);
	}
	while (data)
	{
		// if (pipe_not_followed_by_cmd(data))
		// 	return (1);
		if (check_file_after_redirout(data))
			return (1);
		if (check_file_after_redirin(data))
			return (1);
		if (check_delim_after_heredoc(data))
			return (1);
		data = data->next;
	}
	return (0);
}
