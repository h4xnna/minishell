#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
# include "libft/libft.h"

typedef struct s_global
{
	int	index;
}	t_global;

typedef struct s_data
{
	char			*word;
	char			*type;
	int				index;
	char			**args;
	int				i;
	int				j;
	int				k;
	int				len;
	char			*retour;
	struct s_data	*next;
	struct s_data	*back;
}	t_data;

typedef struct s_List
{
	struct s_data	*begin;
	struct s_data	*end;
}	t_list;

typedef struct s_pipex
{
	int		infilefd;
	int		outfilefd;
	pid_t	*pid;
	int		**pipefd;
	int		count_cmd;
}			t_pipex;

extern int g_r_code;

//minishell_utils
// int		ft_strchr(char *left_char, char c);
// char	*ft_strdup(char *s1);
// char	*ft_strcat(char const *s1, char const *s2);
// char	*ft_strjoin(char const *s1, char const *s2);
// // int		ft_strlen(char const *args);
// size_t  ft_strlen(const char *s);
char	*ft_realloc(char *expanded, char *retour, t_data *data);
int		ft_strcmp(char *s1, char *s2);
char	*ft_itoa(int n);
void	*ft_memset(void *str, int c, size_t len);

//utils
void	ft_free_split(char **split);
int	open_infile(int infilefd, char *infile);
t_pipex	*init_pipex(int ac, char **av);
void	close_pipes(t_pipex *pipex);
int	word_lenght(char const *s, char c);
int	get_out_lenght(char const *s, char c);
char	*special_strdup(char const *s, char c, int *outi);
char	**ft_split(char const *s, char c);
void	free_split(char **out, int i);
void	*ft_calloc(size_t nmemb, size_t size);
char	ft_base(int number);
int		ft_len(int n);

// redirections et pipes
int		get_cmd_nb(t_data *data);
void	ft_first_cmd(int **pipefd, int i);
void	ft_middle_cmd(int **pipefd, int i);
void	ft_last_cmd(int **pipefd, int i);
void	ft_close_all_pipes(int **pipefd, t_data *data, t_list *list);
int		is_redir_in(t_data *data);
void	ft_redir_in(t_data *data);
int		is_redir_out(t_data *data);
void	ft_redir_out(t_data *data);
int		is_redirections(t_data *data);
void	search_redir(t_data *data);
int		is_redir_out_append(t_data *data);
void	ft_redir_out_append(t_data *data);
void	is_redir_start(t_data *data);

//execution
void	get_file(t_list *list);
// void	exec(t_list *list, char **env, t_global global);
int run_pipex(int ac, char **av, char **envp, t_data *data);
void	child_process(t_pipex *pipex, int i, char **av, char **envp,  t_data *data);
void	exect(char *command, char **envp, t_data *data);
void	close_pipes(t_pipex *pipex);
void	print_error(t_list *list, char *args);
void	return_code(t_data *data, char *args, t_global global);

//minishell_utils2
int		is_quote(char c);
int		is_digit(char c);
int		is_operator(char c);
int		ft_strlen_cmd(t_data *data);
int		is_operator2(char *word);

// expansion
void	expansion(t_data *data, char *args);
void	double_quotes_expansion(t_data *data, char *args);
char	*get_var_name(char *retour);
char	*get_expand(char *retour);

//tokenisation
void	get_type(t_data *data, t_list *list);
int		is_cmd(char *word, t_data *data);
int		build_check_path_cmd(char *word, t_data *data, int i, int j);
char	*build_path(char *cmd, char *word);
void	get_word(t_list *list, char *args, t_data *data, t_global global);
int		check_path_cmd(char *word);
void	tokenisation_and_exec(t_list *list, char *args,
			t_global global, char **env);
char	*get_token_type(t_data *data, int *cmd_nb);
void	fill_args_cmd(t_data *data, int k);
void	get_args_cmd(t_data *data, t_list *list);

int		is_chevrons(t_data *data);

// list creation et free
void	free_list(t_list *list);
void	node_creation(t_list *list, char *retour);
void	initialisation(t_data *data, char *args, char **env);
void	free_args_cmd(t_data *temp, int i);

// pars
void	space_pars(t_list *list, t_data *data);
void	operator_pars(t_list *list, t_data *data, char *args);
void	single_quote_pars(t_data *data, char *args);
void	double_quotes_pars(t_data *data, char *args);
void	dollar_pars(t_data *data, char *args, t_global global);
void	dollar_pars_digit_quote(t_data *data, char *args);

// errors pars
int		is_error(char *args);
int		wrong_token_error(t_data *data, t_list *list);
int		is_unclosed_quotes(char *args);

// signals
int		signal_handlers(t_global global);
void	signal_handler(int signum);

// main
void	print_exec(t_list *list, t_global global, char *args, char **env);
void	program_handler(t_list *list, char *args, t_global global, char **env);
#endif