#include "../../includes/builtins.h"

#define PATH_MAX 4000


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
