/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:39:10 by hmimouni          #+#    #+#             */
/*   Updated: 2025/06/27 18:44:49 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	word_lenght(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

void *ft_calloc(size_t count, size_t size)
{
    void *ptr;
    size_t total_size = count * size;
    size_t i;
    unsigned char *p;

    ptr = malloc(total_size);
    if (!ptr)
        return NULL;

    p = (unsigned char *)ptr;
    for (i = 0; i < total_size; i++)
        p[i] = 0;

    return ptr;
}
int	get_out_lenght(char const *s, char c)
{
	int	out;
	int	i;

	i = 0;
	out = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			out++;
			i += word_lenght(s + i, c);
		}
		else
			i++;
	}
	return (out);
}

char	*special_strdup(char const *s, char c, int *outi)
{
	char	*out;
	int		i;

	out = ft_calloc(word_lenght(s, c) + 1, sizeof(char));
	if (out)
	{
		i = 0;
		while (s[i] != c && s[i])
		{
			out[i] = s[i];
			i++;
		}
		*outi += word_lenght(s, c);
	}
	else
		return (NULL);
	return (out);
}



char	**ft_split(char const *s, char c)
{
	char	**out;
	int		i;
	int		j;

	out = ft_calloc(get_out_lenght(s, c) + 1, sizeof(char *));
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			out[j] = special_strdup(s + i, c, &i);
			if (!out[j])
			{
				free_split(out, j);
				return (NULL);
			}
			j++;
		}
		else
			i++;
	}
	return (out);
}