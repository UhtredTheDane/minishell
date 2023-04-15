/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:31:04 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/15 12:57:35 by agengemb         ###   ########.fr       */
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

char	**add_option_a(char **cmd, int size_cmd)
{
	char	**new_cmd;
	int		i;
	int		j;

	new_cmd = malloc(sizeof(char *) * (size_cmd + 2));
	if (!new_cmd)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (j == 1)
			new_cmd[j] = ft_strdup("-a");
		else
			new_cmd[j] = ft_strdup(cmd[i++]);
		if (!new_cmd[j++])
		{
			clean_2d_tab(new_cmd);
			return (NULL);
		}
	}
	new_cmd[j] = NULL;
	return (new_cmd);
}

char	**update_for_grep(char **cmd)
{
	char	**new_cmd;
	int		size_cmd;

	size_cmd = 0;
	while (cmd[size_cmd])
		size_cmd++;
	new_cmd = add_option_a(cmd, size_cmd);
	if (!new_cmd)
		return (cmd);
	clean_2d_tab(cmd);
	return (new_cmd);
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
