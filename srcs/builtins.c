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

int is_unset(t_parse *p, t_cmd *cmd)
{ 
    char *key;

    if (ft_strncmp(cmd->cmd[0], "unset", 5) == 0)
    {
        key = cmd->cmd[1];
        builtin_unset(&p->dico, key);
        return (1);
    }
    return (0);
}

int is_export(t_parse *p, t_cmd *cmd)
{
    char *key;
    char *value;
    char **entries;

    if (ft_strncmp(cmd->cmd[0], "export", 6) == 0)
    {
        entries = ft_split(cmd->cmd[1], '=');
        if (!entries)
            return (0);
        key = entries[0];
        value = entries[1];
        builtin_export(p->dico, key, value);
        free(entries);
        return (1);
    }
    return (0);
}

int is_env(t_parse *p, t_cmd *cmd)
{
    char **envp;

    if (ft_strncmp(cmd->cmd[0], "env", 3) == 0)
    {
        envp = create_envp_tab(p->dico);
        if (!envp)
            return (0);
        builtin_env(envp);
        //free envp
        return (1);
    }
    return (0);
}

int is_exit(t_cmd *cmd)
{
    int return_value;

    if (ft_strncmp(cmd->cmd[0], "exit", 4) == 0)
    {
        return_value = 0;
	if (cmd->cmd[1])
		return_value = ft_atoi(cmd->cmd[1]);
        builtin_exit(return_value);
        return (1);
    }
    return (0);
}

int is_builtin(t_cmd *cmd)
{
    if (ft_strncmp(cmd->cmd[0], "cd", 2) == 0)
        return (1);
    else if (ft_strncmp(cmd->cmd[0], "echo", 4) == 0)
        return (1);
    else if (ft_strncmp(cmd->cmd[0], "pwd", 3) == 0)
        return (1);
    else if (ft_strncmp(cmd->cmd[0], "unset", 5) == 0)
        return (1);
    else if (ft_strncmp(cmd->cmd[0], "export", 6) == 0)
        return (1);
    else if (ft_strncmp(cmd->cmd[0], "env", 3) == 0)
        return (1);
    else if (ft_strncmp(cmd->cmd[0], "exit", 4) == 0)
        return (1);
    return (0);
}
int execute_builtin(t_parse *p, t_cmd *cmd)
{
    if (is_echo(cmd))
        return (1);
    else if (is_pwd(cmd))
        return (1);
    else if (is_cd(p, cmd))
        return (1);
    else if (is_unset(p, cmd))
        return (1);
    else if (is_export(p, cmd))
        return (1);
    else if (is_env(p, cmd))
        return (1);
    else if (is_exit(cmd))
        return (1);
    return (0);
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
    //seulement si existe
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
    printf("exit\n");
    exit(return_value);
}
