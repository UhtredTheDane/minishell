/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:02:24 by agengemb          #+#    #+#             */
/*   Updated: 2023/03/27 15:41:03 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int is_echo(t_cmd *cmd)
{
    if (ft_strncmp(cmd->cmd[0], "echo", 4) == 0)
        return (1);
    return (0);
}
int valid_option(char c)
{
	return(c == 'n');
}

int valid_options(char *s)
{
	int i;
	
	i = 0;
	while(s[i] && s[i] == 'n')
		i++;
	return(s[i] == 1);
}

int check_option(char *cmd_1)
{
	if (!cmd_1)
        return (0);
    if (cmd_1[0] == '-' && ft_strlen(cmd_1) == 2)
    {
        if (cmd_1[1] == 'n' || cmd_1[1] == 'N')
                return (1);
    }
    return (0);
}

int   builtin_echo(t_cmd *cmd)
{
    int i;
    int n_option;

    n_option = check_option(cmd->cmd[1]);
    i = n_option + 1;
    while (cmd->cmd[i])
    {
	    printf("%s", cmd->cmd[i]);
	    if (cmd->cmd[i] != NULL)
		    printf(" ");
	    ++i;
    }
	if (!n_option)
        printf("\n");
    return (0);
}
