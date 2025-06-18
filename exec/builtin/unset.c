#include "../../minishell.h"

int is_valid_identifier(const char *name)
{
    if (!name || !(*name))
        return 0;
    if (!(name[0] == '_' || (name[0] >= 'A' && name[0] <= 'Z') || (name[0] >= 'a' && name[0] <= 'z')))
        return 0;
    for (int i = 1; name[i]; i++)
    {
        if (!(name[i] == '_' || (name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || (name[i] >= '0' && name[i] <= '9')))
            return 0;
    }
    return 1;
}

int remove_env_var(char *name, char ***envp)
{
    int i, j;
    size_t len = strlen(name);
    char **new_env;

   
    for (i = 0; (*envp)[i]; i++);

    new_env = malloc(sizeof(char *) * i); 
    if (!new_env)
        return 1;

    i = 0;
    j = 0;
    while ((*envp)[i])
    {
        if (!(strncmp((*envp)[i], name, len) == 0 && (*envp)[i][len] == '='))
            new_env[j++] = (*envp)[i];
        else
            free((*envp)[i]); 
        i++;
    }
    new_env[j] = NULL;

    free(*envp);
    *envp = new_env;
    return 0;
}

int ft_unset(char **args, char ***envp)
{
    int i = 1;

    while (args[i])
    {
        if (!is_valid_identifier(args[i]))
        {
            fprintf(stderr, "unset: `%s': not a valid identifier\n", args[i]);
        }
        else
        {
            remove_env_var(args[i], envp);
        }
        i++;
    }
    return 0;
}
