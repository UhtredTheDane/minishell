#include "../../../includes/builtins.h"

char  *env_with_no_pwd()
{
    char *old_pwd;

    old_pwd = malloc(sizeof(char));
	if (!old_pwd)
        return (NULL);
	old_pwd[0] = '\0';
    return (old_pwd);
}

int env_with_pwd(t_envp *envp, char *pwd, char **new_pwd, char **old_pwd)
{
	size_t pwd_size;

	pwd_size = ft_strlen(pwd);
    *old_pwd = malloc(sizeof(char) * (pwd_size + 1));
    if (!(*old_pwd))
        return (0);
    ft_strlcpy(*old_pwd, pwd, pwd_size + 1);
    *new_pwd = builtin_pwd();
	if (*new_pwd)
    	set_value(envp, "PWD", *new_pwd);
    else
        return (0);
    return (1);
}

char *replace_home(t_cmd *cmd, char *home)
{
    char *path;
    
    if (cmd->cmd[1] && (cmd->cmd[1][0] == '~'))
    {
        if (ft_strlen(cmd->cmd[1]) != 1)
        {
            path = ft_strjoin(home, cmd->cmd[1] + 1);
            if(!path)
                return (cmd->cmd[1]);
            return (path);
        }
        return (home);
    }
	return (cmd->cmd[1]);
}