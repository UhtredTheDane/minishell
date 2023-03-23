/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:03:30 by agengemb          #+#    #+#             */
/*   Updated: 2023/03/23 18:15:29 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int is_unset(t_parse *p, t_cmd *cmd)
{ 
    char *key;

    if (ft_strncmp(cmd->cmd[0], "unset", 5) == 0)
    {
        key = cmd->cmd[1];
        builtin_unset(&p->envp, key);
        return (1);
    }
    return (0);
}

void    builtin_unset(t_envp **envp, char *key)
{
    delete_key(envp, key);
}
