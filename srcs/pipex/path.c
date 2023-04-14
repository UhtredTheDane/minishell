/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:41:25 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/14 15:37:47 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

char	*format_string(char *name_cmd)
{
	char	*temp;

	temp = ft_strjoin("/", name_cmd);
	if (!temp)
		return (NULL);
	return (temp);
}

char	*test_path(char **all_paths, char *cmd_0)
{
	size_t	i;
	char	*good_path;

	i = 0;
	while (all_paths[i])
	{
		good_path = ft_strjoin(all_paths[i], cmd_0);
		if (!good_path)
			return (NULL);
		if (access(good_path, F_OK) == 0)
			return (good_path);
		++i;
		free(good_path);
	}
	return (NULL);
}

char	*get_path(char *path, char *cmd_0)
{
	char	**all_paths;
	char	*cmd_path;

	all_paths = ft_split(path, ':');
	if (!all_paths)
		return (NULL);
	cmd_path = test_path(all_paths, cmd_0);
	clean_2d_tab(all_paths);
	return (cmd_path);
}

char	*find_path(char **envp, char *cmd, size_t i)
{
	char	*temp;

	temp = get_path(envp[i] + 5, cmd);
	if (!temp)
		return (NULL);
	free(cmd);
	return (temp);
}
