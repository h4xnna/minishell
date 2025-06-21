/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acrusoe <acrusoe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:56:28 by acrusoe           #+#    #+#             */
/*   Updated: 2025/06/19 08:56:28 by acrusoe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	check_path_cmd(char *word)
{
	struct stat	check;

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
	char	*slash;
	char	*string;

	slash = ft_strjoin(cmd, "/");
	string = ft_strjoin(slash, word);
	free(slash);
	return (string);
}

int	build_check_path_cmd(char *word, t_data *data, int i, int j)
{
	char		*slash;
	char		*str;
	char		cmd[256];
	char		*path;

	path = getenv("PATH");
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
	if (ft_strcmp(data->back->word, ">>") == 0)
		return (1);
	if (ft_strcmp(data->back->word, "<") == 0)
		return (1);
	return (0);
}

int	is_cmd(char *word, t_data *data)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (data->back && is_chevrons(data))
		return (0);
	if (check_path_cmd(word))
		return (1);
	if (build_check_path_cmd(word, data, i, j))
		return (1);
	return (0);
}

// char	*find_path(char *cmd, char **envp)
// {
// 	char	**paths;
// 	char	*full_path;
// 	int		i;
// 	char	*tmp;

// 	i = 0;
// 	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
// 		i++;
// 	if (!envp[i])
// 		return (NULL);
// 	paths = ft_split(envp[i] + 5, ':');
// 	if (!paths)
// 		return (NULL);
// 	i = 0;
// 	while (paths[i])
// 	{
// 		tmp = ft_strjoin(paths[i], "/");
// 		full_path = ft_strjoin(tmp, cmd);
// 		free(tmp);
// 		if (access(full_path, F_OK | X_OK) == -1)
// 		{
// 			free(full_path);
// 			free(paths[i]);
// 			i++;
// 		}
// 		else
// 		{
// 			while (paths[i])
// 			{
// 				free(paths[i]);
// 				i++;
// 			}
// 			free(paths);
// 			return (full_path);
// 		}
// 	}
// 	free(paths);
// 	return (NULL);
// }
