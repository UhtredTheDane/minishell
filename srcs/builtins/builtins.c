/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 01:25:34 by agengemb          #+#    #+#             */
/*   Updated: 2023/03/25 19:37:55 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

#define PATH_MAX 4000

int is_builtin(t_cmd *cmd)
{
    if (cmd && cmd->cmd)
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
    }
    return (0);
}

int execute_builtin(t_parse *p, t_cmd *cmd)
{

    if (is_cd(cmd))
    {
        return (builtin_cd(p->envp, cmd));
    }
    else if (is_echo(cmd))
        return (builtin_echo(cmd));
    else if (is_env(cmd))
        return (builtin_env(p->envp, cmd));
    else if (is_exit(cmd))
        return (builtin_exit(p->envp, cmd));
    else if (is_pwd(cmd))
    {
        print_pwd();
        return (0);
    }


    /*
    else if (is_unset(p, cmd))
        return (1);
    else if (is_export(p, cmd))
        return (1);
*/






    return (0);
}
