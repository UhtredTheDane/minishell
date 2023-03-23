/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:02:24 by agengemb          #+#    #+#             */
/*   Updated: 2023/03/23 18:14:25 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int is_echo(t_cmd *cmd)
{
    int n_option;
    int i;
    char *message;

    if (ft_strncmp(cmd->cmd[0], "echo", 4) == 0)
    {
        n_option = 0;
	message = "";
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

void    builtin_echo(const char *message, int n_option)
{
    printf("%s", message);
    if (!n_option)
        printf("\n");
}