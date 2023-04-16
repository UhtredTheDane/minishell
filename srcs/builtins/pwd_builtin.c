/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:02:46 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/14 16:29:40 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	is_pwd(t_cmd *cmd)
{
	size_t	size;

	size = ft_strlen(cmd->cmd[0]);
	if (size < 3)
		size = 3;
	if (ft_strncmp(cmd->cmd[0], "pwd", size) == 0)
		return (1);
	return (0);
}

char	*builtin_pwd(t_cmd *cmd)
{
	char	*buffer;

	buffer = ft_calloc(PATH_MAX + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	if (!getcwd(buffer, PATH_MAX))
	{
		printf("%s: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n", cmd->cmd[0]);
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

void	print_pwd(t_cmd *cmd)
{
	char	*pwd;

	pwd = builtin_pwd(cmd);
	if (pwd)
	{
		printf("%s\n", pwd);
		free(pwd);
	}
}
