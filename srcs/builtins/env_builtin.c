/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:03:01 by agengemb          #+#    #+#             */
/*   Updated: 2023/03/23 18:14:35 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int is_env(t_cmd *cmd)
{
    if (ft_strncmp(cmd->cmd[0], "env", 3) == 0)
        return (1);
    return (0);
}

int    builtin_env(t_envp *envp, t_cmd *cmd)
{
    char **char_envp;
    int i;

    if (cmd->cmd[1])
    {
        printf("env: '%s': No such file or directory\n", cmd->cmd[1]);
        return (127);
    }
    char_envp = create_envp_tab(envp);
    if (!char_envp)
        return (1);
    i = 0;
    while (char_envp[i])
    {
        printf("%s\n", char_envp[i]);
        ++i;
    }
    return (0);
}
