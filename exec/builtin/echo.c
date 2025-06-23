/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 21:40:34 by hmimouni          #+#    #+#             */
/*   Updated: 2025/06/23 23:18:14 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int	is_valid_n_option(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int ft_strncmp(char *s1, char *s2, int n)
{
	int i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		i++;
	}
	return(s1[i] - s2[i]);
}

void ft_echo(char **av)
{
	int i = 1;
	int newline = 1;

	if (av)
	{
		while(av[i] && ft_strncmp(av[i], "-n", 2) == 0 && is_valid_n_option(av[i]))
		{
			newline = 0;
			i++;
		}
		while(av[i])
		{
			printf("%s", av[i]);
			if(av[i + 1])
			{
				printf("%s", " ");
			}
			i++;
		}
	}
	if(newline)
		printf("\n");
	exit(0);
}