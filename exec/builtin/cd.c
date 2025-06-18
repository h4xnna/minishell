#include "../../minishell.h"

extern char **environ;

char *get_env_value(const char *name)
{
    int i = 0;
    size_t len = strlen(name);

    while (environ[i])
    {
        if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
            return environ[i] + len + 1;
        i++;
    }
    return NULL;
}

void set_env_var(const char *key, const char *value)
{
    char *env_str = malloc(strlen(key) + strlen(value) + 2); 
    if (!env_str)
        return;

    sprintf(env_str, "%s=%s", key, value);
    putenv(env_str);
}


int ft_cd(char **args)
{
    char *path = NULL;
    char cwd[1024];
    char *oldpwd = getcwd(NULL, 0);

    if (!oldpwd)
        perror("getcwd");

    if (!args[1])
    {
        path = get_env_value("HOME");
        if (!path)
        {
            fprintf(stderr, "cd: HOME not set\n");
            free(oldpwd);
            return 1;
        }
    }
    else
        path = args[1];

    if (chdir(path) != 0)
    {
        perror("cd");
        free(oldpwd);
        return 1;
    }

    if (oldpwd)
        set_env_var("OLDPWD", oldpwd);
    if (getcwd(cwd, sizeof(cwd)))
        set_env_var("PWD", cwd);

    free(oldpwd);
    return 0;
}
