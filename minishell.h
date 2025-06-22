/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/06/21 09:33:42 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/21 09:33:42 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

// typedef struct s_env
// {
// 	char *valeur;
// 	//tous ce qu'il y a apres le '='
// 	char *cle;
// 	//tous ce qu'il y a avant le '='
// }	t_env


typedef struct s_List
{
	struct s_data *begin;
	struct s_data *end;
} t_list;

// exec..execution
void	get_file(t_list *list);
int	is_redirections(t_data *data);
void	exec(t_list *list, char **env, t_global global);

// exec ../expansion
char	*get_var_name(char *retour);
char	*get_expand(char *retour);
void	operator_pars(t_list *list, t_data *data, char *args);
void	single_quote_pars(t_data *data, char *args);
void	expansion(t_data *data, char *args);
void	double_quotes_expansion(t_data *data, char *args);

// exec../path_cmd
int	check_path_cmd(char *word);
int	build_check_path_cmd(char *word, t_data *data, int i, int j);
char	*build_path(char *cmd, char *word);
int	is_chevrons(t_data *data);
int	is_cmd(char *word, t_data *data);

// exec../pipes
void	ft_first_cmd(int **pipefd, int i);
void	ft_middle_cmd(int **pipefd, int i);
void	ft_last_cmd(int **pipefd, int i);
void	ft_close_all_pipes(int **pipefd, t_data *data, t_list *list);

//exec../builtin../echo
int ft_echo(char **av);
int	is_valid_n_option(char *str);
int ft_strncmp(char *s1, char *s2, int n);

//exec../builtin../pwd
int	ft_pwd(void);

//exec../builtin../unset


//exec../builtin../cd
char	*get_env_value(const char *name, char **envp);
char	*make_env_str(const char *key, const char *value);
int	update_env_var(const char *key, const char *value, char ***envp);
int	handle_path(char **args, char ***envp, char **path);
int	ft_cd(char **args, char ***envp);


//exec../builtin../export



//exec../builtin../exit
int	ft_exit(char **args);




// pars../list_creation
void	get_word(t_list *list, char *args, t_data *data, t_global global);
void	node_creation(t_list *list, char *retour);
void	initialisation(t_data *data, char *args, char **env);

// pars../parsing_function
void	space_pars(t_list *list, t_data *data);
void	operator_pars(t_list *list, t_data *data, char *args);
void	single_quote_pars(t_data *data, char *args);
void	double_quotes_pars(t_data *data, char *args);

// pars../args_cmd
int	is_operator2(char *word);
void	fill_args_cmd(t_data *data, int k);
void	get_args_cmd(t_data *data, t_list *list);
int	get_cmd_nb(t_data *data);


// pars../dollar_hanling_functions
void	dollar_pars(t_data *data, char *args, t_global global);
void	dollar_pars_digit_quote(t_data *data, char *args);

// pars../get_return_code
void	return_code(t_data *data, char *args, t_global global);
 void	print_splash_screen(void);
 void	test_builtins(t_data *data, char **env);

// pars../print_command_error
int	is_error(char *args);
void	print_error(t_list *list, char *args);


// pars../redirection_in
int	is_redir_in(t_data *data);
void	ft_redir_in(t_data *data);

// pars../redirection_out
int	is_redir_out(t_data *data);
void	ft_redir_out(t_data *data);
int	is_redir_out_append(t_data *data);
void	ft_redir_out_append(t_data *data);

// pars../tokenisation
void	get_type(t_data *data, t_list *list);
char	*get_token_type(t_data *data, int *cmd_nb);

// utils../free_mmory
void	free_args_cmd(t_data *temp, int i);
void	free_list(t_list *list);

// utils../ft_itoa
char	*ft_itoa(int n);
void	ft_char(char number, long i, long nbr, char *str);
int	ft_length(long n);


// utils../minishell_utils
int	ft_strchr(char *left_char, char c);
char	*ft_strdup(char *s1);
char	*ft_strcat(char const *s1, char const *s2);
char	*ft_strjoin(char const *s1, char const *s2);
int	ft_strlen(char const *args);
int	ft_strcmp(char *s1, char *s2);

// utils../minishell_utils2
int	is_quote(char c);
int	is_digit(char c);
int	is_operator(char c);
int	ft_strlen_cmd(t_data *data);
void	*ft_memset(void *str, int c, size_t len);
char	*ft_realloc(char *expanded, char *retour, t_data *data);

// utils../redirection_checker
void	search_redir(t_data *data);
void	is_redir_start(t_data *data);

// utils../syntax_error_token
int	wrong_token_error(t_data *data, t_list *list);
int	check_delim_after_heredoc(t_data *data);
int	pipe_not_followed_by_cmd(t_data *data);
int	check_file_after_redirout(t_data *data);



//util../return_code
int	set_get_exit_status(int exit_code);

// signal
int	signal_handlers();
void	signal_handler(int signum);

// main
int	is_unclosed_quotes(char *args);
void	print_exec(t_list *list, t_global global, char *args, char **env);
void	tokenisation_and_exec(t_list *list, char *args, t_global global,
		char **env);
void	program_handler(t_list *list, char *args, t_global global, char **env);

char	ft_base(int number);
int	ft_len(int n);

#endif