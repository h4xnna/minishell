/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:10:58 by hmimouni          #+#    #+#             */
/*   Updated: 2024/11/15 20:01:06 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*out;
	int		i;
	int		j;

	out = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	i = 0;
	if (out)
	{
		j = 0;
		while (s1[j])
		{
			out[i] = s1[j];
			i++;
			j++;
		}
		j = 0;
		while (s2[j])
		{
			out[i] = s2[j];
			i++;
			j++;
		}
		out[i] = '\0';
	}
	return (out);
}
