# include "minishell.h"
#include <string.h>
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' && s2[i] != '\0'))
		i++;
	return (s1[i] - s2[i]);

}

void	exec(t_list *list, char **env)
{
	t_data *data = list->begin;
	pid_t pid;
	int status;

	while (data)
	{
		if (ft_strcmp(data->type, "CMD") == 0)
		{
			
			pid = fork();
			if (pid < 0)
			{
				perror("fork failed");
				exit(EXIT_FAILURE);
			}
			else if (pid == 0)
			{
				execve(data->word, data->args, env);
				perror("execve failed");
				exit(EXIT_FAILURE);
			}
		}
		data = data->next;
	}
	waitpid(-1, &status, 0);	
}

// int return_code(char *const argv[])
// {
// 	pid_t pid = fork();
// 	int status;
// 	int code;

// 	if (pid == -1) {
// 		perror("Erreur lors du fork");
// 		return (-1);
// 	}

// 	if (pid == 0) 
// 	{
// 		execvp(argv[0], argv);
// 		perror("Échec exec");
// 		exit(127);  
// 	}

// 	if (waitpid(pid, &status, 0) == -1) 
// 	{
// 		perror("Erreur lors de waitpid");
// 		return (-1);
// 	}
// 	if (WIFEXITED(status))
// 	{
// 		code = WEXITSTATUS(status);
// 		return (code);
// 	}
// 	else if (WIFSIGNALED(status))
// 	{
// 		code = WTERMSIG(status);
// 		return (128 + code); 
// 	}
// }

// void	grep_exec(char **args)
// {
// 	int	pipefd[2];
	
// 	pid_t pid1;
// 	pid_t pid2;
// 	int	status;

// 	pipe(pipefd);
// 	pid1 = fork();
// 	if (pid1 == 0)
// 	{
// 		dup2(pipefd[1], 1);
// 		close (pipefd[0]);
// 		execve("/usr/bin/ls", data->args, envp);

// 	}
// 	pid2 = fork();
// 	if (pid2 == 0)
// 	{
// 		dup2(pipefd[0], 0);
// 		close (pipefd[1]);
// 		execve("/usr/bin/grep", data->args, envp);
// 	}
// 	close(pipefd[0]);
// 	close(pipefd[1]);
// 	waitpid(pid1, &status, 0);
// 	waitpid(pid2, &status, 0);
// 	if (waitpid(pid, &status, 0) == -1) 
// 	{
// 		perror("Erreur lors de waitpid");
// 		return (-1);
// 	}
// 	if (WIFEXITED(status))
// 		data->rcode = WEXITSTATUS(status);
// 	else if (WIFSIGNALED(status))
// 		data->rcode = WTERMSIG(status)  + 128;
// }

int	ft_strlen(char const *args)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	while (args[i])
		i++;
	return (i);
}

char	*ft_realloc(char *expanded, char *retour, t_data *data)
{
	int		length;
	int		i;
	char	*str;
	int		k;

	length = ft_strlen(retour) + ft_strlen(expanded);
	str = malloc(sizeof(char) * (length + 1));
	k = 0;
	if (!str)
		return (NULL);
	i = 0;
	while (retour[i])
	{
		str[i] = retour[i];
		i++;
	}
	while (expanded[k])
		str[i++] = expanded[k++];
	str[i] = '\0';
	free (retour);
	free(expanded);
	data->j = i;
	return (str);
}

int	is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == '>' || c == '<' || c == ' ' || c == '|')
		return (1);
	return (0);
}

int	ft_strchr(char *left_char, char c)
{
	int		i;

	i = 0;
	while (left_char[i] != '\0')
	{
		if (left_char[i] == c)
		{
			i++;
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strdup(char *s1)
{
	char	*str;
	size_t	i;
	size_t	len;

	len = ft_strlen(s1);
	str = malloc((len + 1) * sizeof(char));
	i = 0;
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strcat(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str1;
	int		len1;
	int		len2;

	i = 0;
	j = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str1 = malloc((len1 + len2 + 1) * sizeof(char));
	if (!str1 || !s1 || !s2)
		return (NULL);
	while (s1[i] != '\0')
	{
		str1[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		str1[i++] = s2[j++];
	str1[i] = '\0';
	return (str1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strcat;

	strcat = ft_strcat(s1, s2);
	return (strcat);
}

int	ft_strlen_cmd(t_data *data)
{
	int	i;

	i = 0;
	while (data && ft_strcmp(data->word, "|") != 0)
	{
		if (ft_strcmp(data->type, "CMD") == 0)
			i++;
		if (ft_strcmp(data->type, "ARG") == 0)
			i++;
		data = data->next;
	}
	return (i);
}

void	print_list(t_list *list)
{
	t_data *data;
	int	i;
	int j;

	data = list->begin;
	// while (data)
	// {
	// 	i = 0;
	// 	if (ft_strcmp(data->type, "CMD") == 0)
	// 	{
	// 		while (data->args[i] != NULL)
	// 		{
	// 			j = 0;
	// 			while (data->args[i][j])
	// 			{
	// 				printf("%c", data->args[i][j]);
	// 				j++;
	// 			}
	// 			printf("\n");
	// 			i++;
	// 		}
	// 	}
	// 	data = data->next;
	// }
	while (data)
	{
		printf("%s\n", data->type);
		printf("%s\n", data->word);
		data = data->next;
	}
}

char	*get_var_name(char *retour)
{
	int		i;
	int		j;
	char	*str;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen(retour);
	str = malloc(sizeof(char) * (len + 1));
	while (retour[i] != '$')
		i++;
	i++;
	while (retour[i] && retour[i] != ' ' && retour[i] != '\'')
	{
		str[j] = retour[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*get_expand(char *retour)
{
	char	*env_value;
	char	*var;
	int		i;
	int		j;
	int len;

	len = ft_strlen(retour);
	i = 0;
	j = 0;
	var =  get_var_name(retour);
	if (!var[0])
		return(ft_strdup("$"));
	else
		env_value = ft_strdup(getenv(var));
	return (env_value);
}

void	free_list(t_list *list)
{
	t_data	*data;
	t_data	*temp;

	data = list->begin;
	if (!list)
		return ;
	while (data)
	{
		temp = data;
		data = data->next;
		free(temp);
	}
	list->begin = NULL;
	free(list);
}

void	node_creation(t_list *list, char *retour)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit (1);
	data->word = ft_strdup(retour);
	data->next = NULL;
	data->back = NULL;
	if (list->end == NULL)
	{
		list->begin = data;
		list->end = data;
	}
	else
	{
		list->end->next = data;
		data->back = list->end;
		list->end = data;
	}
}

void	get_file(t_list *list)
{
	t_data *data;

	data = list->begin;
	while (data)
	{
		if (ft_strcmp(data->type, "REDIR_OUT") == 0)
		{
			if (data->next && ft_strcmp(data->next->type, "ARG") == 0)
				data->next->type = "FILE";
			else if (data->next && ft_strcmp(data->next->type, "SPACE") == 0)
			{
				data = data->next;
				while (data && ft_strcmp(data->type, "SPACE") == 0)
					data = data->next;
				if (ft_strcmp(data->type, "ARG") == 0)
					data->type = "FILE";
			}
		}
		data = data->next;
	}
}

int	is_operator2(char *word) 
{
	char *operators[] = {"|", ">", "<", ">>", NULL};
	int i = 0;

	while (operators[i]) {
		if (ft_strcmp(word, operators[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	fill_args_cmd(t_data *data, int k)
{
	t_data *cmd;
	int len;

	cmd = data;
	len = ft_strlen_cmd(data);
	cmd->args = malloc(sizeof(char *) * (len + 1));
	while (data && !is_operator2(data->word))
	{
		if (ft_strcmp(data->type, "CMD") == 0)
		{
			cmd->args[k] = data->word;
			k++;
		}
		else if (ft_strcmp(data->type, "ARG") == 0)
		{
			cmd->args[k] = data->word;
			k++;
		}
		data = data->next;
	}
	cmd->args[k] = NULL;
}

void	get_args_cmd(t_data *data, t_list *list)
{
	int k;

	k = 0;
	data = list->begin;
	while (data)
	{
		if (ft_strcmp(data->type, "CMD") == 0)
		{
			fill_args_cmd(data, k);
			while (data && !is_operator2(data->word))
				data = data->next;
		}
		else
			data = data->next;
	}
}

int	is_cmd(char *word, t_data *data)
{
	char	*path;
	char	*slash;
	char	*str;
	char	cmd[256];
	int		i;
	int		j;
	struct 	stat check;

	path = getenv("PATH");
	i = 0;
	if (access(word, X_OK) == 0)
	{
		if (stat(word, &check) == 0)
		{
			if (S_ISREG(check.st_mode))
				return (1);
		}
	}
	while (path[i])
	{
		j = 0;
		while (path[i] && path[i] != ':')
			cmd[j++] = path[i++];
		cmd[j] = '\0';
		slash = ft_strjoin(cmd, "/");
		str = ft_strjoin(slash, word);
		if (access(str, X_OK) == 0)
		{
			if (stat(str, &check) == 0)
			{
				if (S_ISREG(check.st_mode))
				{
					data->word = ft_strdup(str);
					return (1);
				}
			}
		}
		i++;
	}
	
	return (0);
}

void	get_type(t_data *data, t_list *list)
{
	data = list->begin;
	while (data)
	{
		if (is_cmd(data->word, data))
			data->type = "CMD";
		else if (ft_strcmp(data->word, ">") == 0)
			data->type = "REDIR_OUT";
		else if (ft_strcmp(data->word, "<") == 0)
			data->type = "REDIR_IN";
		else if (ft_strcmp(data->word, ">>") == 0)
			data->type = "REDIR_OUT_2";
		else if (ft_strcmp(data->word, "<<") == 0)
			data->type = "HEREDOC";
		else if (ft_strcmp(data->word, "\0") == 0)
			data->type = "SPACE";
		else if (ft_strcmp(data->word, "|") == 0)
			data->type = "PIPE";
		else
			data->type = "ARG";
		data = data->next;
	}
}

void	space_pars(t_list *list, t_data *data)
{
	if (data->j > 0)
	{
		data->retour[data->j] = '\0';
		node_creation(list, ft_strdup(data->retour));
		data->j = 0;
		data->retour[data->j] = '\0';
		node_creation(list, ft_strdup(data->retour));
	}
	data->i++;
}

void	operator_pars(t_list *list, t_data *data, char *args)
{
	if (data->j > 0)
	{
		data->retour[data->j] = '\0';
		node_creation(list, ft_strdup(data->retour));
		data->j = 0;
	}
	if (args[data->i] == '>' && args[data->i + 1] == '>')
	{
		node_creation(list, ft_strdup(">>"));
		data->i += 2;
	}
	else if (args[data->i] == '<' && args[data->i + 1] == '<')
	{
		node_creation(list, ft_strdup("<<"));
		data->i += 2;
	}
	else
	{
		data->retour[0] = args[data->i++];
		data->retour[1] = '\0';
		node_creation(list, ft_strdup(data->retour));
	}	
}

void	single_quote_pars(t_data *data, char *args)
{
	data->i++;
	while (args[data->i] && args[data->i] != '\'')
		data->retour[data->j++] = args[data->i++];
	if (args[data->i] == '\'')
		data->i++;
	else
		exit (1);
}

void	expansion(t_data *data, char *args)
{
	int		k;
	char	*var;
	int		len;
	char	*expand;

	k = 0;
	len = ft_strlen(args);
	var = malloc(sizeof(char) * (len + 1));
	expand = ft_strdup("");
	var[k++] = '$';
	while (args[data->i] && !is_operator(args[data->i]) && !is_quote(args[data->i])
		&& args[data->i] != '$')
		var[k++] = args[data->i++];
	var[k] = '\0';
	expand = get_expand(var);
	data->retour[data->j] = '\0';
	data->retour = ft_realloc(expand, data->retour, data);
	free(var);
}

void	double_quotes_expansion(t_data *data, char *args)
{
	char	*expanded;
	char	*temp;
	int		k;
	int		len;

	expanded = ft_strdup("");
	len = ft_strlen(args);
	temp = malloc(sizeof(char) * (len + 1));
	data->i++;
	k = 0;
	temp[k++] = '$';
	while (args[data->i] && !is_quote(args[data->i]) && args[data->i] != '$' && args[data->i] != ' ')
		temp[k++] = args[data->i++];
	temp[k] = '\0';
	expanded = get_expand(temp);
	data->retour[data->j] = '\0';
	data->retour = ft_realloc(expanded, data->retour, data);
	free(temp);
}

void	double_quotes_pars(t_data *data, char *args)
{
	data->i++;
	while (args[data->i] && args[data->i] != '"')
	{
		if (args[data->i] == '$')
			double_quotes_expansion(data, args);
		else
			data->retour[data->j++] = args[data->i++];
	}
	if (args[data->i] == '"')
		data->i++;
	else 
		exit (1);
}

// void	return_code(t_data *data, char *args)
// {
// 	int	i;
// 	char *code;

// 	i = 0;
// 	if (data->index == 1)
// 		data->retour[data->j++] = '0';
// 	else
// 	{
// 		code = ft_itoa(data->rcode);
// 		while (code[i])
// 			data->retour[data->j++] = code[i++];
// 		free(code);
// 	}
// }

void	dollar_pars(t_data *data, char *args)
{
	char c;

	data->i++;
	if (is_digit(args[data->i]) || is_quote(args[data->i]))
	{
		c = args[data->i];
		data->i++;
		if (is_quote(args[data->i - 1]))
		{
			while (args[data->i] && !is_quote(args[data->i]))
				data->retour[data->j++] = args[data->i++];
			if (args[data->i] == c)
				data->i++;
			else
				exit (1);
		}
		while (is_digit(args[data->i]))
			data->i++;
	}
	else if (args[data->i] == '=' || args[data->i] == '%')
		data->retour[data->j++] = '$';
	// else if (args[data->i] == '?')
	// 	return_code(data, args);
	else
		expansion(data, args);
}

void get_word(t_list *list, char *args, t_data *data)
{
	while (args[data->i] == ' ')
		data->i++;
	while (args[data->i])
	{
		if (args[data->i] == ' ')
			space_pars(list, data);
		else if (args[data->i] == '"')
			double_quotes_pars(data,args);
		else if (args[data->i] == '\'')
			single_quote_pars(data, args);
		else if (is_operator(args[data->i]))
			operator_pars(list, data, args);
		else if (args[data->i] == '$')
			dollar_pars(data, args);
		else
			data->retour[data->j++] = args[data->i++];
	}
	if (data->j > 0)
	{
		data->retour[data->j] = '\0';
		node_creation(list, ft_strdup(data->retour));
	}
	free(data->retour);
}

void	initialisation(t_data *data, char *args, char **env)
{
	data->i = 0;
	data->j = 0;
	data->k = 0;
	data->index = 0;
	data->len = ft_strlen(args);
	data->retour = malloc(sizeof(char) * (data->len + 1));
	data->envp = env;
}

int	main(int ac, char **av, char **env)
{
	t_list *list;
	t_data	*data;
	char *args;

	data = malloc(sizeof(t_data));
	list = malloc(sizeof(t_list));
	if (!list ||!data)
		return (0);
	list->begin = NULL;
	list->end = NULL;
	while (1)
	{
		if (list->begin)
			data = list->begin;
		args = readline("Minishell > ");
		add_history(args);
		initialisation(data, args, env);
		data->index++;
		get_word(list, args, data);
		get_type(data, list);
		get_args_cmd(data, list);
		get_file(list);
		// print_list(list);
		exec(list, env);
		rl_redisplay();
		free_list(list);
	}
	return (0);
}