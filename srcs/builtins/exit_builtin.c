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

int is_exit(t_cmd *cmd)
{
    if (ft_strncmp(cmd->cmd[0], "exit", 4) == 0)
        return (1);
    return (0);
}

int is_all_digit(char *str)
{
    size_t i;

    i = 0;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        ++i;
    }
    return (1);
}

int    builtin_exit(t_envp *envp, t_cmd *cmd)
{
    int return_value;

    printf("exit\n");
    return_value = 0;
    if (cmd->cmd[2])
    {
        printf("bash : exit: too many arguments\n");
        return (1)
    }
    if (cmd->cmd[1])
    {
        if (!is_all_digit(cmd->cmd[1]))
        {
            printf("bash : exit: %s: numeric argument required\n", cmd->cmd[1]);
            return_value = 1;
        }
        else
            return_value = ft_atoi(cmd->cmd[1]);
    }
    delete_dico(&envp);
    exit(return_value);
}