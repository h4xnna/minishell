/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:42:28 by hmimouni          #+#    #+#             */
/*   Updated: 2025/07/14 18:50:52 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_heredoc(t_data *data)
{
	if (data->type && !ft_strcmp(data->type, "HERE_DOC"))
		return (1);
	return (0);
}
void	ft_bzero(void *s, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}

int	get_allocation(char const *s, int start, int len)
{
	if (start >= ft_strlen(s))
		return (0);
	if (len < ft_strlen(s + start))
		return (len);
	return (ft_strlen(s + start));
}
void	*ft_calloc(int nmemb, int size)
{
	void	*out;

	out = malloc(nmemb * size);
	if (!out)
		return (NULL);
	ft_bzero(out, nmemb * size);
	return (out);
}

char	*ft_substr(char const *s, int start, int len)
{
	char	*out;
	int		i;

	i = 0;
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	out = ft_calloc(get_allocation(s, start, len) + 1, sizeof(char));
	if (!out)
		return (NULL);
	if (start >= ft_strlen(s))
		return (out);
	while (i < len && s[i + start])
	{
		out[i] = s[i + start];
		i++;
	}
	out[i] = '\0';
	return (out);
}

char	*search_in_env(char *expand, t_list_env *env)
{
	char	*out;
	t_env	*tmp;

	tmp = env->begin;
	while (tmp != env->end)
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
char	*ft_realloc2(char *expanded, char *retour)
{
	int		length;
	int		i;
	char	*str;
	int		k;

	length = ft_strlen(retour) + ft_strlen(expanded);
	str = malloc(sizeof(char) * (length + 2));
	k = 0;
	if (!str)
		return (NULL);
	i = 0;
	while (retour[i])
	{
		str[i] = retour[i];
		i++;
	}
	while (expanded && expanded[k])
		str[i++] = expanded[k++];
	str[i] = '\0';
	free(retour);
	return (str);
}

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
			if(line[i + 1] == '?')
			{
				exit_code = set_get_exit_status(-1);
				line[i] = exit_code;
				
			}
			
			i++;
			start = i;
			while (ft_isalnum(line[i]))
			{
				i++;
			}
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

void	here_doc(t_data *data, t_list_env *env)
{
	int		fd;
	char	*line;

	(void)data;
	line = NULL;
	if (!data->next || !data)
		return ;
	if (!data->here_doc_fd)
	{
		data->here_doc_fd = open("here_doc", O_TRUNC | O_CREAT | O_RDWR, 0677);
		if (data->here_doc_fd < 0)
			return ;
	}
	fd = data->here_doc_fd;
	while ((line = readline("\033[1m\033[31mheredoc → \033[0m")) != NULL
		&& ft_strcmp(data->next->word, line) != 0)
	{
		line = expand_line(line, env);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	close(fd);
	if (data->next->next && ft_strcmp(data->next->next->type, "CMD") == 0)
	{
		// printf("%s", data->next->next->type);
		fd = open("here_doc", O_RDONLY);
		if (fd < 0)
			return ;
		dup2(fd, STDIN_FILENO);
		unlink("here_doc");
		close(fd);
	}
}
