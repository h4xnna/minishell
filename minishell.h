#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_global
{
	int index;
} t_global;

typedef struct s_data
{
	char *word;
	char *type;
	int index;
	char **args;
	int i;
	int j;
	int k;
	int len;
	char *retour;
	struct s_data *next;
	struct s_data *back;
} t_data;

typedef struct s_List
{
	struct s_data *begin;
	struct s_data *end;
} t_list;

typedef struct s_pipex
{
	int infilefd;
	int outfilefd;
	pid_t *pid;
	int **pipefd;
	int count_cmd;
} t_pipex;

extern int g_r_code;
// args_cmd
int	is_operator2(char *word);
void	fill_args_cmd(t_data *data, int k);
void	get_args_cmd(t_data *data, t_list *list);
int	get_cmd_nb(t_data *data);

// execution
void	get_file(t_list *list);
// void	exec(t_list *list, char **env, t_global global);
int	run_pipex(int ac, char **av, char **envp, t_data *data);

void	child_process(t_pipex *pipex, int i, char **av, char **envp,
		t_data *data);
void	exect(char *command, char **envp, t_data *data);
void	close_pipes(t_pipex *pipex);

// expeansion
char	*get_var_name(char *retour);
char	*get_expand(char *retour);
void	expansion(t_data *data, char *args);
void	double_quotes_expansion(t_data *data, char *args);

// itoa
char	*ft_itoa(int n);

// list_creation
void	get_word(t_list *list, char *args, t_data *data, t_global global);
void	node_creation(t_list *list, char *retour);
void	initialisation(t_data *data, char *args, char **env);

// main
void	print_list(t_list *list, char *args);
void	free_list(t_list *list);
void	get_type(t_data *data, t_list *list);
void	return_code(t_data *data, char *args, t_global global);
int	is_error(char *args);
int	is_unclosed_quotes(char *args);
void	test_builtins(t_data *data, char **env);

// minishell_utils
// int		ft_strchr(char *left_char, char c);
// char	*ft_strdup(char *s1);
// char	*ft_strcat(char const *s1, char const *s2);
// char	*ft_strjoin(char const *s1, char const *s2);
// // int		ft_strlen(char const *args);
// size_t  ft_strlen(const char *s);
char	*ft_realloc(char *expanded, char *retour, t_data *data);
int	ft_strcmp(char *s1, char *s2);

// minishell_utils2
int	is_quote(char c);
int	is_digit(char c);
int	is_operator(char c);
int	ft_strlen_cmd(t_data *data);
void	*ft_memset(void *str, int c, size_t len);

// parsing_function
void	space_pars(t_list *list, t_data *data);
void	operator_pars(t_list *list, t_data *data, char *args);
void	single_quote_pars(t_data *data, char *args);
void	double_quotes_pars(t_data *data, char *args);
void	dollar_pars(t_data *data, char *args, t_global global);

// path_cmmand
int	is_cmd(char *word, t_data *data);
char	*find_path(char *cmd, char **envp);

// utils
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

// exec...echo
int	is_valid_n_option(char *str);
int	ft_echo(char **av);

// exec...cd
int ft_cd(char **args);
// char *get_env_value(const char *name);
// void set_env_var(const char *key, const char *value);

// exec...unset
int	is_valid_identifier(const char *name);
int	remove_env_var(char *name, char ***envp);
int	ft_unset(char **args, char ***envp);

// pipes
void	ft_first_cmd(int **pipefd, int i);
void	ft_middle_cmd(int **pipefd, int i);
void	ft_last_cmd(int **pipefd, int i);
void	ft_close_all_pipes(int **pipefd, t_data *data, t_list *list);

// redirection
int	is_redir_in(t_data *data);
void	ft_redir_in(t_data *data);
int	is_redir_out(t_data *data);
void	ft_redir_out(t_data *data);
int	is_redir_out_append(t_data *data);
void	ft_redir_out_append(t_data *data);
void	search_redir(t_data *data);

// signal
int	signal_handlers(void);
void	signal_handler(int signum);

char	ft_base(int number);
int	ft_len(int n);

#endif