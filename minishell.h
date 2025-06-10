# ifndef MINI_SHELL_H
# define MINI_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

typedef struct s_data
{
	char			*word;
	char			*type;
	int				index;
	char			**args;
	char			**envp;
	int				i;
	int				j;
	int				k;
	int				len;
	int				rcode;
	char			*retour;
	struct s_data	*next;
	struct s_data	*back;
}t_data;

typedef struct s_List
{
	struct s_data	*begin;
	struct s_data	*end;
}t_list;

#endif