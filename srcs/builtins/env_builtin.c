/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:03:01 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/14 16:31:30 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	is_env(t_cmd *cmd)
{
	size_t	size;

	size = ft_strlen(cmd->cmd[0]);
	if (size < 3)
		size = 3;
	if (ft_strncmp(cmd->cmd[0], "env", size) == 0)
		return (1);
	return (0);
}

int	builtin_env(t_envp *envp, t_cmd *cmd)
{
	int		i;
	char	**char_envp;

	if (cmd->cmd[1])
	{
		printf("env: '%s': No such file or directory\n", cmd->cmd[1]);
		return (127);
	}
	char_envp = create_envp_tab(envp);
	if (!char_envp)
		return (1);
	i = 0;
	while (char_envp[i])
	{
		printf("%s\n", char_envp[i]);
		free(char_envp[i]);
		++i;
	}
	free(char_envp);
	return (0);
}
