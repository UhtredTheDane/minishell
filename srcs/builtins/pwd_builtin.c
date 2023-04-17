/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:02:46 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/17 19:40:42 by agengemb         ###   ########.fr       */
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

char	*builtin_pwd(t_parse *p, char *cmd)
{
	char	*buffer;
	char	*error;
	char	*access;

	buffer = ft_calloc(PATH_MAX + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	if (!getcwd(buffer, PATH_MAX))
	{
		if (p)
		{
			error = ft_strjoin(cmd, ": error retrieving current directory: getcwd: ");
			access = "cannot access parent directories: No such file or directory\n";
			write(p->default_out, error, ft_strlen(error));
			write(p->default_out, access, ft_strlen(access));
			free(error);
		}
		else
		{
			printf("%s: error retrieving current directory: getcwd: ", cmd);
			printf("cannot access parent directories: No such file or directory\n");
		}
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

int	print_pwd(t_parse *p)
{
	char	*pwd;

	pwd = builtin_pwd(p, "pwd");
	if (!pwd)
		return (1);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
