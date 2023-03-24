/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:02:36 by agengemb          #+#    #+#             */
/*   Updated: 2023/03/24 22:09:51 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int is_exit(t_parse *p, t_cmd *cmd)
{
    int return_value;

    if (ft_strncmp(cmd->cmd[0], "exit", 4) == 0)
    {
        return_value = 0;
	if (cmd->cmd[1])
		return_value = ft_atoi(cmd->cmd[1]);
        builtin_exit(p->envp, return_value);
        return (1);
    }
    return (0);
}

void    builtin_exit(t_envp *envp, int return_value)
{
    printf("exit\n");
    delete_dico(&envp);
    exit(return_value);
}
