/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:02:46 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/07 15:40:31 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	is_pwd(t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd[0], "pwd", 3) == 0)
		return (1);
	return (0);
}

char	*builtin_pwd(void)
{
	char	*buffer;

	buffer = ft_calloc(PATH_MAX + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	if (!getcwd(buffer, PATH_MAX))
	{
		perror("Erreur getcwd\n");
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

void	print_pwd(void)
{
	char	*pwd;

	pwd = builtin_pwd();
	if (pwd)
	{
		printf("%s\n", pwd);
		free(pwd);
	}
}
