#include "../includes/pipex.h"
#include "../includes/bultins.h"

#define PATH_MAX 4000

int is_echo(t_cmd *cmd)
{
    int n_option;
    int i;
    char *message;

    if (ft_strncmp(cmd->cmd[0], "echo", 4) == 0)
    {
        n_option = 0;
        i = 1;
        while (cmd->cmd[i])
        {
            if (cmd->cmd[i][0] == '-')
            {
                if (cmd->cmd[i][1] == 'n' || cmd->cmd[i][1] == 'N')
                    n_option = 1;
            }
            else
                message = cmd->cmd[i];
            ++i;
        }
        builtin_echo(message, n_option);
        return (1);
    }
    return (0);
}

int is_pwd(t_cmd *cmd)
{
    if (ft_strncmp(cmd->cmd[0], "pwd", 3) == 0)
    {
        printf("%s\n", builtin_pwd());
        return (1);
    }
    return (0);
}

int is_cd(t_parse *p, t_cmd *cmd)
{
    if (ft_strncmp(cmd->cmd[0], "cd", 2) == 0)
    {
        builtin_cd(p->dico, cmd->cmd[1]);
        return (1);
    }
    return (0);
}

//int is_unset()

int is_builtin(t_parse *p, t_cmd *cmd)
{
    if (is_echo(cmd))
        return (1);
    else if (is_pwd(cmd))
        return (1);
    else if (is_cd(p, cmd))
        return (1);
    else
    {
        printf("sa passe par ici\n");
        return (0);
    }
    /*
    else if (is_unset())
        return (1);
    else if (is_export())
        return (1);
    else if (is_env())
        return (1);
    else if (is_exit())
        return (1);*/
}

void    builtin_echo(const char *message, int n_option)
{
    printf("%s", message);
    if (!n_option)
        printf("\n");
}

char *builtin_pwd()
{
    char    *buffer;

    buffer = ft_calloc(PATH_MAX + 1, sizeof(char));
    if (!buffer)
        return (NULL);
    if (!getcwd(buffer, PATH_MAX))
    {
        perror("Erreur getcwd\n");
        free(buffer);
        return (NULL);
    }
    return (buffer);
}

int builtin_cd(t_dico *dico, const char *path)
{
    char    *old_pwd;
    char    *new_pwd;
    char    *pwd;
    size_t pwd_size;

    if (chdir(path) == -1)
    {
        perror("Erreur cd\n");
        return (0);
    }
    pwd = getvalue(dico, "PWD");
    pwd_size = ft_strlen(pwd);
    old_pwd = malloc(sizeof(char) * (pwd_size + 1));
    if (!old_pwd)
        return (0);
    ft_strlcpy(old_pwd, pwd, pwd_size + 1);
    new_pwd = builtin_pwd();
    set_value(dico, "OLDPWD", old_pwd);
    set_value(dico, "PWD", new_pwd);
    return (1);
}

void    builtin_unset(t_dico **dico, char *key)
{
    delete_key(dico, key);
}

int    builtin_export(t_dico *dico, char *key, char *value)
{
    t_dico *new;

    new = ft_diconew(key, value);
    if (!new)
        return (0);
    ft_dicoadd(&dico, new);
    return (1);
}

void    builtin_env(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        printf("%s\n", envp[i]);
        ++i;
    }
}

void    builtin_exit(int return_value)
{
    printf("exit");
    exit(return_value);
}