/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 22:41:33 by hmimouni          #+#    #+#             */
/*   Updated: 2025/06/22 23:03:06 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"


static int	is_numeric(const char *str)
{
	int	i = 0;

	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
static long	ft_atol(const char *str)
{
	int		sign = 1;
	long	result = 0;

	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
		result = result * 10 + (*str++ - '0');
	return (sign * result);
}
static int	is_overflow(const char *str)
{
	long long	res = 0;
	int			sign = 1;
	int			i = 0;

	if (str[0] == '+' || str[0] == '-')
	{
		if (str[0] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		res = res * 10 + (str[i] - '0');
		if ((sign == 1 && res > 2147483647 ) || (sign == -1 && -res < -2147483648))
			return (1);
		i++;
	}
	return (0);
}

int	ft_exit(char **args)
{
	long	code;

	printf("exit\n");
	if (!args[1])
		exit(0);
	if (!is_numeric(args[1]) || is_overflow(args[1]))
	{
		dprintf( 2,"exit: %s: numeric argument required\n", args[1]);
		exit(255);
	}
	if (args[2])
	{
		dprintf(2, "exit: too many arguments\n");
		return (1);
	}
	code = ft_atol(args[1]);
	exit((unsigned char)code);
}
