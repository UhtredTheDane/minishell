/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:02:24 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/16 00:52:56 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	is_echo(t_cmd *cmd)
{
	size_t	size;

	size = ft_strlen(cmd->cmd[0]);
	if (size < 4)
		size = 4;
	if (ft_strncmp(cmd->cmd[0], "echo", size) == 0)
		return (1);
	return (0);
}

int	check_options(char *s, char option)
{
	int	i;

	i = 1;
	while (s[i])
	{
		if (s[i] != option)
			return (0);
		++i;
	}
	return (1);
}

int	check_option(char *cmd)
{
	if (!cmd)
		return (0);
	if (cmd[0] == '-')
	{
		if (check_options(cmd, 'n') || check_options(cmd, 'N'))
			return (1);
	}
	return (0);
}

int	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	n_option;

	n_option = 0;
	i = 1;
	while (cmd->cmd[i] && check_option(cmd->cmd[i]))
		++i;
	if (i > 1)
		n_option = 1;
	while (cmd->cmd[i])
	{
		printf("%s", cmd->cmd[i]);
		++i;
		if (cmd->cmd[i] != NULL)
			printf(" ");
	}
	if (!n_option)
		printf("\n");
	return (0);
}
