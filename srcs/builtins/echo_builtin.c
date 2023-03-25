/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:02:24 by agengemb          #+#    #+#             */
/*   Updated: 2023/03/25 00:54:01 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int is_echo(t_cmd *cmd)
{
    int n_option;

    if (ft_strncmp(cmd->cmd[0], "echo", 4) == 0)
    {
        n_option = 0;
	if (cmd->cmd[1][0] == '-')
        {
            if (cmd->cmd[1][1] == 'n' || cmd->cmd[1][1] == 'N')
                n_option = 1;
        }
        builtin_echo(cmd->cmd, n_option);
        return (1);
    }
    return (0);
}

void    builtin_echo(char **messages, int n_option)
{
    int i;

    i = n_option + 1;
    while (messages[i])
{
	printf("%s", messages[i]);
	if (messages[i + 1] != NULL)
		printf(" ");
	++i;
}
	if (!n_option)
        printf("\n");
}
