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

int ft_echo(char **av)
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
	return(0);
}
