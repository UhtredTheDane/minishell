/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:31:04 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/15 20:01:20 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"
#include <sys/types.h>
#include <dirent.h>

int	char_in_str(char c, char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		++i;
	}
	return (0);
}

int	test_acces(t_cmd *cmd)
{
	if (access(cmd->cmd[0], F_OK) == -1)
	{
		printf("minishell: %s: No such file or directory\n", cmd->cmd[0]);
		return (127);
	}
	if (access(cmd->cmd[0], X_OK) == -1)
	{
		printf("minishell: %s: Permission denied\n", cmd->cmd[0]);
		return (126);
	}
	return (0);
}

int	test_directory(char *cmd)
{
	DIR	*directory;

	if (cmd[0] == '/')
	{
		directory = opendir(cmd);
		if (directory)
		{
			printf("minishell: %s: Is a directory\n", cmd);
			closedir(directory);
			return (0);
		}
		closedir(directory);
	}
	return (1);
}
