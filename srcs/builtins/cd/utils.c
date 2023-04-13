/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:56:35 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/13 00:19:08 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/builtins.h"

int	size_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[i])
		++i;
	return (i);
}

char	*env_with_no_pwd(void)
{
	char	*old_pwd;

	old_pwd = malloc(sizeof(char));
	if (!old_pwd)
		return (NULL);
	old_pwd[0] = '\0';
	return (old_pwd);
}

int	env_with_pwd(t_envp *envp, char *pwd, char **new_pwd, char **old_pwd)
{
	size_t	pwd_size;

	pwd_size = ft_strlen(pwd);
	*old_pwd = malloc(sizeof(char) * (pwd_size + 1));
	if (!(*old_pwd))
		return (0);
	ft_strlcpy(*old_pwd, pwd, pwd_size + 1);
	*new_pwd = builtin_pwd();
	if (*new_pwd)
		set_value(envp, "PWD", *new_pwd);
	else
		return (0);
	return (1);
}

char	*replace_home(t_cmd *cmd, char *default_folder)
{
	char	*path;
	char	*initial_path;

	initial_path = ft_strdup(cmd->cmd[1]);
	if (cmd->cmd[1] && (cmd->cmd[1][0] == '~'))
	{
		if (ft_strlen(cmd->cmd[1]) != 1)
		{
			path = ft_strjoin(default_folder, cmd->cmd[1] + 1);
			if (!path)
				return (initial_path);
			return (path);
		}
		return (default_folder);
	}
	return (initial_path);
}
