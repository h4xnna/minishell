#include "../minishell.h"

int is_builtin(char *word)
{
	if (ft_strcmp(word, "echo") == 0)
		return (1);
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
	char *path;
	char *slash;
	char *str;
	char cmd[256];
	int i;
	int j;
	struct stat check;

	if (is_builtin(word))
		return (1);
	path = getenv("PATH");
	i = 0;
	if (data->back && is_chevrons(data))
		return (0);
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