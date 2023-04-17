/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:23:32 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/17 15:49:55 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	execute_cmd(t_parse *p, t_cmd *cmd, int old_stdin, int old_stdout)
{
	int	exec_return;

	prepare_cmd(cmd);
	if (is_builtin(cmd))
	{
		exec_return = execute_builtin(p, cmd);
		dup2(old_stdin, 0);
		dup2(old_stdout, 1);
	}
	else
		exec_return = run_cmd(p, cmd);
	close(old_stdin);
	close(old_stdout);
	return (exec_return);
}

int	manager(t_parse *p, t_cmd *cmd, int num_proc, int builtin)
{
	int	num_write;
	int	num_read;
	int	old_stdin;
	int	old_stdout;

	if ((p->pipes_fd || !builtin) && !init_not_interactive_signals(1))
		return (0);
	set_num_pipe(p, &num_read, &num_write, num_proc);
	close_useless_pipes(p, num_read, num_write);
	old_stdin = dup(0);
	old_stdout = dup(1);
	if (!redirect_stdin(p, cmd, num_read)
		|| !redirect_stdout(p, cmd, num_write))
	{
		close(old_stdin);
		close(old_stdout);
		return (2);
	}
	return (execute_cmd(p, cmd, old_stdin, old_stdout));
}

int	execute(t_parse *p, t_envp *envp)
{
	int	rt;

	rt = 1;
	rt = edit_parsing(p, envp);
	if (rt)
		return (rt);
	if (!split_cmd(p))
		return (1);
	replace_dollards(p, envp);
	if (!p->pipes_fd && is_builtin(p->first))
		g_rt = manager(p, p->first, 0, 1);
	else if (!run_pipe(p))
	{
		printf("Impossible de lancer les pipes\n");
		return (1);
	}
	return (0);
}
