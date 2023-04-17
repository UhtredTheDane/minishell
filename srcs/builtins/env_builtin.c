/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:03:01 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/14 23:39:58 by agengemb         ###   ########.fr       */
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

void	show_env(t_envp *envp)
{
	int		i;
	char	**char_envp;

	char_envp = create_envp_tab(envp);
	if (char_envp)
	{
		i = 0;
		while (char_envp[i])
		{
			printf("%s\n", char_envp[i]);
			free(char_envp[i]);
			++i;
		}
		free(char_envp);
	}	
}

int	builtin_env(t_parse *p, t_envp *envp, t_cmd *cmd)
{
	char	*error;

	if (cmd->cmd[1])
	{	
		error = ft_strjoin(cmd->cmd[1], ": No such file or directory\n");
		write(p->default_out, "env: '", 6);
		write(p->default_out, error, ft_strlen(error));
		free(error);
		return (127);
	}
	show_env(envp);
	return (0);
}
