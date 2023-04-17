/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:31:04 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/17 18:56:35 by agengemb         ###   ########.fr       */
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

int	test_acces(t_parse *p, t_cmd *cmd)
{
	char	*error;

	if (access(cmd->cmd[0], F_OK) == -1)
	{
		error = ft_strjoin(cmd->cmd[0], ": No such file or directory");
		write(p->default_out, error, ft_strlen(error));
		free(error);
		return (127);
	}
	if (access(cmd->cmd[0], X_OK) == -1)
	{
		error = ft_strjoin(cmd->cmd[0], ": Permission denied\n");
		write(p->default_out, error, ft_strlen(error));
		free(error);
		return (126);
	}
	return (0);
}

int	test_directory(t_parse *p, char *cmd)
{
	DIR	*directory;
	char	*error;

	if (cmd[0] == '/')
	{
		directory = opendir(cmd);
		if (directory)
		{
			error = ft_strjoin(cmd, ": Is a directory\n");
			write(p->default_out, error, ft_strlen(error));
			free(error);
			closedir(directory);
			return (0);
		}
		closedir(directory);
	}
	return (1);
}

int	first_test(t_parse *p, char **cmd)
{
	if (cmd && cmd[0])
	{
		if (ft_strlen(cmd[0]) == 1 && (cmd[0][0] == ':'
			|| cmd[0][0] == '!'))
			return (0);
		if (!test_directory(p, cmd[0]))
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
	if (!test_directory(p, cmd))
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
