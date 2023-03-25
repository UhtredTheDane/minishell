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

int is_unset(t_cmd *cmd)
{ 

    if (ft_strncmp(cmd->cmd[0], "unset", 5) == 0)
        return (1);
    return (0);
}

void    builtin_unset(t_envp **envp, t_cmd *cmd)
{
    char *key;
    char *test;


    test = getenv("SHLVL");
    if (test)
        printf("c'est une basic !");
    else
        printfc("ce n'est pas une basic !");
        
    key = cmd->cmd[1];
    delete_key(envp, key);


}
