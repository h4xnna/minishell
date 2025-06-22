/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 22:14:49 by hmimouni          #+#    #+#             */
/*   Updated: 2025/06/22 22:15:10 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_env_value(const char *name, char **envp)
{
	int		i;
	size_t	len;

	i = 0;
	len = strlen(name);
	while (envp[i])
	{
		if (strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*make_env_str(const char *key, const char *value)
{
	char	*new_entry;

	new_entry = malloc(strlen(key) + strlen(value) + 2);
	if (!new_entry)
		return (NULL);
	sprintf(new_entry, "%s=%s", key, value);
	return (new_entry);
}

int	update_env_var(const char *key, const char *value, char ***envp)
{
	int		i;
	size_t	key_len;
	char	*new_entry;
	char	**new_envp;

	key_len = strlen(key);
	new_entry = make_env_str(key, value);
	if (!new_entry)
		return (1);
	i = 0;
	while ((*envp)[i])
	{
		if (strncmp((*envp)[i], key, key_len) == 0
			&& (*envp)[i][key_len] == '=')
		{
			free((*envp)[i]);
			(*envp)[i] = new_entry;
			return (0);
		}
		i++;
	}
	new_envp = realloc(*envp, sizeof(char *) * (i + 2));
	if (!new_envp)
		return (free(new_entry), 1);
	new_envp[i] = new_entry;
	new_envp[i + 1] = NULL;
	*envp = new_envp;
	return (0);
}
int	handle_path(char **args, char ***envp, char **path)
{
	if (!args[1])
	{
		*path = get_env_value("HOME", *envp);
		if (!*path)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return (1);
		}
	}
	else
		*path = args[1];
	return (0);
}

int	ft_cd(char **args, char ***envp)
{
	char	*path;
	char	cwd[1024];
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		perror("getcwd");
	if (handle_path(args, envp, &path))
		return (free(oldpwd), 1);
	if (chdir(path) != 0)
	{
		perror("cd");
		return (free(oldpwd), 1);
	}
	if (oldpwd)
		update_env_var("OLDPWD", oldpwd, envp);
	if (getcwd(cwd, sizeof(cwd)))
		update_env_var("PWD", cwd, envp);
	return (free(oldpwd), 0);
}
