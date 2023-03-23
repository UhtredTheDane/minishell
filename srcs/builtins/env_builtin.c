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

int is_env(t_parse *p, t_cmd *cmd)
{
    char **envp;

    if (ft_strncmp(cmd->cmd[0], "env", 3) == 0)
    {
        envp = create_envp_tab(p->envp);
        if (!envp)
            return (0);
        builtin_env(envp);
        //free envp
        return (1);
    }
    return (0);
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
