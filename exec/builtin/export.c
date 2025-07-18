/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:07:09 by hmimouni          #+#    #+#             */
/*   Updated: 2025/07/18 22:25:41 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	env_list_add_back(t_list_env *env_list, t_env *new_node)
{
	if (!env_list || !new_node)
		return ;
	if (!env_list->begin)
	{
		env_list->begin = new_node;
		env_list->end = new_node;
	}
	else
	{
		env_list->end->next = new_node;
		new_node->back = env_list->end;
		env_list->end = new_node;
	}
	new_node->next = NULL;
}

t_env	*env_list_find(t_list_env *env_list, char *key)
{
	t_env	*current;

	current = env_list->begin;
	while (current)
	{
		if (strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	split_key_value(char *str, char **key, char **value)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	*key = strndup(str, i);
	if (str[i] == '=')
		*value = strdup(str + i + 1);
	else
		*value = strdup("");
}

t_env	*new_env_node(char *str)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	split_key_value(str, &node->key, &node->value);
	node->next = NULL;
	node->back = NULL;
	return (node);
}

void	update_existing_env(t_env *existing_node, char *key, char *value)
{
	free(existing_node->value);
	existing_node->value = value;
	free(key);
}

void	add_new_env(t_list_env *envp, char *arg, char *key, char *value)
{
	t_env *new_node;

	new_node = new_env_node(arg);
	if (new_node)
		env_list_add_back(envp, new_node);
	free(key);
	free(value);
}

void	handle_export_argument(t_list_env *envp, char *arg)
{
	t_env *existing_node;
	char *key;
	char *value;

	if (!is_valid_identifier(arg))
	{
		dprintf(2, "export: invalid identifier: %s\n", arg);
		return ;
	}
	split_key_value(arg, &key, &value);
	existing_node = env_list_find(envp, key);
	if (existing_node)
		update_existing_env(existing_node, key, value);
	else
		add_new_env(envp, arg, key, value);
}

void	ft_export(t_list_env *envp, char **args)
{
	int i;

	if (!args || !args[0])
		return ;
	i = 1;
	while (args[i])
	{
		handle_export_argument(envp, args[i]);
		i++;
	}
}
