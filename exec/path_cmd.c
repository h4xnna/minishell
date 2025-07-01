/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 18:36:50 by hmimouni          #+#    #+#             */
/*   Updated: 2025/06/29 18:36:50 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


int	check_path_cmd(char *word)
{
	struct stat check;

	if (access(word, X_OK) == 0)
	{
		if (stat(word, &check) == 0)
		{
			if (S_ISREG(check.st_mode))
				return (1);
		}
	}
	return (0);
}

char	*build_path(char *cmd, char *word)
{
	char *slash;
	char *string;

	slash = ft_strjoin(cmd, "/");
	string = ft_strjoin(slash, word);
	free(slash);
	return (string);
}

int	build_check_path_cmd(char *word, t_data *data, int i, int j,
		t_list_env *env)
{
	char *str;
	char cmd[256];
	char *path;

	path = NULL;
	while (env->begin)
	{
		if (ft_strcmp(env->begin->key, "PATH") == 0)
		{
			path = env->begin->value;
			break ;
		}
		else
			env->begin = env->begin->next;
	}
	if (!path)
		return (1);
	while (path[i])
	{
		j = 0;
		while (path[i] && path[i] != ':')
			cmd[j++] = path[i++];
		cmd[j] = '\0';
		str = build_path(cmd, word);
		if (check_path_cmd(str))
		{
			free(data->word);
			data->word = str;
			return (1);
		}
		free(str);
		i++;
	}
	return (0);
}

int	is_chevrons(t_data *data)
{
	if (ft_strcmp(data->back->word, ">") == 0)
		return (1);
	else if (ft_strcmp(data->back->word, ">>") == 0)
		return (1);
	else if (ft_strcmp(data->back->word, "<") == 0)
		return (1);
	else if (ft_strcmp(data->back->word, "<<") == 0)
		return (1);
	return (0);
}

int	built_cmd_child(char *str)
{
	if (strcmp(str, "echo") == 0)
		return (1);
	else if (strcmp(str, "pwd") == 0)
		return (1);
	else if (strcmp(str, "env") == 0)
		return (1);
	return (0);
}

int	built_cmd_parent(char *str)
{
	if (strcmp(str, "cd") == 0)
		return (1);
	else if (strcmp(str, "export") == 0)
		return (1);
	else if (strcmp(str, "unset") == 0)
		return (1);
	else if (strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

int	is_cmd(char *word, t_data *data, t_list_env *env)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (data->back && is_chevrons(data))
		return (0);
	if (built_cmd_parent(word))
		return (1);
	if (built_cmd_child(word))
		return (1);
	if (check_path_cmd(word))
		return (1);
	if (build_check_path_cmd(word, data, i, j, env))
		return (1);
	return (0);
}
