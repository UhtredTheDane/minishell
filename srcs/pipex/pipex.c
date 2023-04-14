/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:41:38 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/14 23:01:56 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

char	*make_cmd(t_parse *p, char *name_cmd)
{
	char	*cmd;
	char	*tempo_cmd;
	size_t	i;
	char	**envp;

	envp = create_envp_tab(p->envp);
	cmd = format_string(name_cmd);
	if (!cmd)
		return (clean_2d_tab(envp), NULL);
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		++i;
	if (!envp[i])
		return (free(cmd), clean_2d_tab(envp), NULL);
	tempo_cmd = find_path(envp, cmd, i);
	clean_2d_tab(envp);
	if (!tempo_cmd)
		return (free(cmd), NULL);
	return (tempo_cmd);
}

char	*search_cmd(t_parse *p, t_cmd *cmd)
{
	char	*cmd_name;
	size_t	size;

	size = ft_strlen(cmd->cmd[0]);
	if (cmd->cmd[0][0] == '\0')
		return (cmd->cmd[0]);
	if (ft_strncmp(cmd->cmd[0], ".", size) == 0
		|| ft_strncmp(cmd->cmd[0], "..", size) == 0)
		return (NULL);
	cmd_name = make_cmd(p, cmd->cmd[0]);
	if (!cmd_name)
		return (NULL);
	return (cmd_name);
}

void	waiting_all_sons(size_t nb_sons, pid_t last)
{
	size_t	i;
	pid_t	pid;
	int		status;

	status = 0;
	i = 0;
	while (i < nb_sons)
	{
		pid = waitpid(-1, &status, 0);
		if (WIFEXITED(status) && pid == last)
			g_rt = WEXITSTATUS(status);
		++i;
	}
}

pid_t	create_process(t_parse *p)
{
	pid_t	pid;
	t_cmd	*current;
	int		return_code;
	int		i;

	i = 0;
	current = p->first;
	while (current)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("Probleme fork");
			return (0);
		}
		else if (pid == 0)
		{
			return_code = manager(p, current, i, 0);
			free_parse(p);
			exit(return_code);
		}
		++i;
		current = current->next;
	}
	return (pid);
}

int	run_pipe(t_parse *p)
{
	pid_t	pid;

	pid = create_process(p);
	if (!pid)
		return (0);
	if (!update_not_interactive_sigint(0))
		return (0);
	close_all_pipes(p);
	if (p->count == 0)
		p->count = 1;
	waiting_all_sons(p->count, pid);
	if (p->first->pipe_heredoc)
		close(p->first->pipe_heredoc[0]);
	if (!update_interactive_sigint())
		return (1);
	return (1);
}
