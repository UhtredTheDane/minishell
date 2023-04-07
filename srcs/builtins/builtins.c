/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 01:25:34 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/07 16:52:09 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

#define PATH_MAX 4000

int	is_builtin(t_cmd *cmd)
{
	int	res;

	res = 0;
	if (cmd && cmd->cmd)
	{
		res = is_cd(cmd) || is_export(cmd) || is_echo(cmd) || is_env(cmd) || is_exit(cmd) || is_pwd(cmd) || is_unset(cmd);
	}
	return (res);
}

int	execute_builtin(t_parse *p, t_cmd *cmd)
{
	if (is_cd(cmd))
		return (builtin_cd(p->envp, cmd));
	else if (is_echo(cmd))
		return (builtin_echo(cmd));
	else if (is_env(cmd))
		return (builtin_env(p->envp, cmd));
	else if (is_exit(cmd))
		return (builtin_exit(p->envp, cmd));
	else if (is_pwd(cmd))
	{
		print_pwd();
		return (0);
	}
	else if (is_unset(cmd))
		return (builtin_unset(p, cmd));
	else if (is_export(cmd))
		return (builtin_export(p->envp, cmd));
	return (0);
}
