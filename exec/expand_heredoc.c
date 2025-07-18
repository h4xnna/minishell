/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 19:37:52 by hmimouni          #+#    #+#             */
/*   Updated: 2025/07/18 22:26:35 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	append_to_expanded(char **expanded, char *text, int *j)
// {
// 	char	*tmp;
// 	int		len;

// 	if (!text)
// 		return ;
// 	len = ft_strlen(text);
// 	tmp = ft_realloc2(text, *expanded);
// 	if (tmp)
// 	{
// 		*expanded = tmp;
// 		*j += len;
// 	}
// 	free(text);
// }

// void	handle_dollar(char *line, int *i, int *j, char **expanded,
// 		t_list_env *env)
// {
// 	char	*key;
// 	char	*out;
// 	int		start;
// 	int		exit_code;

// 	(*i)++;
// 	if (line[*i] == '?')
// 	{
// 		exit_code = set_get_exit_status(-1);
// 		append_to_expanded(expanded, ft_itoa(exit_code), j);
// 		(*i)++;
// 	}
// 	else
// 	{
// 		start = *i;
// 		while (ft_isalnum(line[*i]))
// 			(*i)++;
// 		key = ft_substr(line, start, *i - start);
// 		out = search_in_env(key, env);
// 		if (out)
// 			append_to_expanded(expanded, out, j);
// 		free(key);
// 	}
// }

// void	handle_expansion(char *line, int *i, int *j, char **expanded,
// 		t_list_env *env)
// {
// 	if (line[*i] == '$')
// 		handle_dollar(line, i, j, expanded, env);
// 	else
// 	{
// 		(*expanded)[*j] = line[*i];
// 		(*i)++;
// 		(*j)++;
// 	}
// }

// char	*expand_line(char *line, t_list_env *env)
// {
// 	int		i;
// 	int		j;
// 	char	*expanded;
// 	int		len;

// 	i = 0;
// 	j = 0;
// 	len = ft_strlen(line);
// 	expanded = ft_calloc(1, sizeof(char) * (len + 1));
// 	if (!expanded)
// 		return (NULL);
// 	expanded[len] = '\0';
// 	while (line[i])
// 		handle_expansion(line, &i, &j, &expanded, env);
// 	return (expanded);
// }

char	*expand_line(char *line, t_list_env *env)
{
	int		i;
	int		j;
	char	*key;
	char	*expanded;
	int		start;
	int		len;
	char	*out;
	int exit_code;

	i = 0;
	j = 0;

	len = ft_strlen(line);
	expanded = ft_calloc(1, sizeof(char) * (len + 1));
	if (!expanded)
	return (NULL);
	expanded[len] = '\0';
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			if(line[i] == '?')
			{
				exit_code = set_get_exit_status(-1);
				expanded = ft_realloc2(ft_itoa(exit_code), expanded);
				j += ft_strlen(ft_itoa(exit_code));
				i++;
				continue ;
			}
			start = i;
			while (ft_isalnum(line[i]))
				i++;
			key = ft_substr(line, start, i - start);
			out = search_in_env(key, env);
			if (out)
			{
				expanded = ft_realloc2(out, expanded);
				j += ft_strlen(out);
			}
			free(key);
		}
		else
		{
			expanded[j] = line[i];
			i++;
			j++;
		}
	}
	return (expanded);
}
