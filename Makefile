BOLD            = "\033[1m"
RESET           = "\033[0m"
GREEN           = "\033[0;32m"
CYAN            = "\033[0;36m"
LIGHT_RED       = "\033[91m"
LIGHT_GREEN     = "\033[92m"
LIGHT_CYAN      = "\033[96m"
BROWN           = "\033[38;5;94m"

NEON_GREEN      = "\033[38;5;46m"
ELECTRIC_BLUE   = "\033[38;5;51m"
HOT_PINK        = "\033[38;5;198m"
BLOOD_RED       = "\033[38;5;196m"
SUNBURST_YELLOW = "\033[38;5;226m"
DEEP_ORANGE     = "\033[38;5;208m"
PURPLE_RAVE     = "\033[38;5;129m"
CYAN_SHOCK      = "\033[38;5;51m"



NAME	= minishell
CC		= cc 
CFLAGS	= -Wall -Werror -Wextra -g3 


LIBFT_PATH        = libft/
LIBFT_NAME        = libft.a
LIBFT            = $(LIBFT_PATH)$(LIBFT_NAME)

SRCS	=	pars/args_cmds.c\
			exec/execution.c\
			exec/expansion.c\
			pars/ft_itoa.c\
			pars/list_creation.c\
			main.c\
			pars/minishell_utils.c\
			pars/minishell_utils2.c\
			pars/parsing_functions.c\
			exec/path_cmd.c\
			exec/pipes.c\
			exec/redirections.c\
			exec/utils.c\
			signals.c


OBJS = ${SRCS:.c=.o}

all: ${NAME}

%.o: %.c 
	@$(CC) $(CFLAGS) -I. -c $< -o $@

${NAME}: ${OBJS} $(LIBFT) 

	@echo $(LIGHT_GREEN) "Compilation..."$(BOLD)
	@${CC} ${CFLAGS} ${OBJS} $(LIBFT) -lreadline -lhistory -o ${NAME}
	@echo $(LIGHT_GREEN)"Compilation réussie ✔"$(RESET)

$(LIBFT):
	@make -sC libft -j

clean:
	@rm -f ${OBJS}
	@make -sC libft clean -j
	@echo $(BROWN)clean reussi

fclean: clean
	@rm -f ${NAME}
	@make -sC libft clean -j
	@echo $(BROWN)fclean reussi

re: fclean all

.PHONY : re fclean clean all