/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:31:04 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/16 02:12:21 by agengemb         ###   ########.fr       */
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

int	first_test(char **cmd)
{
	if (cmd && cmd[0])
	{
		if (ft_strlen(cmd[0]) == 1 && (cmd[0][0] == ':'
			|| cmd[0][0] == '!'))
			return (0);
		if (!test_directory(cmd[0]))
			return (126);
		return (1);
	}
	return (0);
}

int	already_with_path(t_parse *p, char *cmd)
{
	char	**all_path;
	size_t	i;
	size_t	size;

	if (cmd[0] == '.' && cmd[1] == '/')
		return (1);
	if (!test_directory(cmd))
		return (126);
	all_path = ft_split(get_value(p->envp, "PATH"), ':');
	if (!all_path)
		return (0);
	i = 0;
	while (all_path[i])
	{
		size = ft_strlen(all_path[i]);
		if (ft_strncmp(all_path[i], cmd, size) == 0)
		{
			clean_2d_tab(all_path);
			return (1);
		}
		++i;
	}
	clean_2d_tab(all_path);
	return (0);
}
