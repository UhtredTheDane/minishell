/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:02:36 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/14 16:28:40 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	is_exit(t_cmd *cmd)
{
	size_t	size;

	size = ft_strlen(cmd->cmd[0]);
	if (size < 4)
		size = 4;
	if (ft_strncmp(cmd->cmd[0], "exit", size) == 0)
		return (1);
	return (0);
}

int	is_all_digit(char *str)
{
	size_t	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i = 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		++i;
	}
	return (1);
}

int	builtin_exit(t_envp *envp, t_cmd *cmd)
{
	int	return_value;

	printf("exit\n");
	return_value = 0;
	if (cmd->cmd[1])
	{
		if (!is_all_digit(cmd->cmd[1]))
		{
			printf("bash : exit: %s: numeric argument required\n", cmd->cmd[1]);
			return_value = 2;
		}
		else
		{
			if (cmd->cmd[2])
			{
				printf("bash : exit: too many arguments\n");
				return (1);
			}
			return_value = ft_atoi(cmd->cmd[1]);
		}
	}
	delete_dico(envp);
	exit(return_value);
}
