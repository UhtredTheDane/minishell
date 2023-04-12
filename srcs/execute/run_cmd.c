/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:25:39 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/13 00:35:39 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

char	*init_pos_first(int *current_pos, int quote_pos, int double_pos)
{
	if (quote_pos <= double_pos)
	{
		*current_pos = quote_pos;
		return ("'");
	}
	else
	{
		*current_pos = double_pos;
		return ("\"");
	}
}

char	*rm_first(char *cmd, int *current_pos, int quote_pos, int double_pos)
{
	char	*first;
	char	*tempo_str;

	first = init_pos_first(current_pos, quote_pos, double_pos);
	if (*current_pos != (int)ft_strlen(cmd))
	{
		cmd[*current_pos] = '\0';
		tempo_str = ft_strjoin(cmd, cmd + *current_pos + 1);
		if (!tempo_str)
			return (NULL);
		free(cmd);
		cmd = tempo_str;
		*current_pos = skip_to_X(cmd, *current_pos, first);
		cmd[*current_pos] = '\0';
		tempo_str = ft_strjoin(cmd, cmd + *current_pos + 1);
		if (!tempo_str)
			return (cmd);
		free(cmd);
		cmd = tempo_str;
	}
	return (cmd);
}

char	*trim_quotes(char *cmd)
{
	char	*trim_cmd;
	int		current_pos;
	int		quote_pos;
	int		double_pos;

	current_pos = 0;
	trim_cmd = ft_strdup(cmd);
	while (trim_cmd[current_pos])
	{
		quote_pos = skip_to_X(trim_cmd, current_pos, "'");
		double_pos = skip_to_X(trim_cmd, current_pos, "\"");
		trim_cmd = rm_first(trim_cmd, &current_pos, quote_pos, double_pos);
		if (!trim_cmd)
			return (cmd);
	}
	return (trim_cmd);
}

void	prepare_cmd(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	if (cmd->cmd)
	{
		if (cmd->heredoc && ft_strncmp(cmd->cmd[0], "grep", 4) == 0)
			cmd->cmd = update_for_grep(cmd->cmd);
		while (cmd->cmd[i])
		{
			cmd->cmd[i] = trim_quotes(cmd->cmd[i]);
			++i;
		}
	}
}

int	run_cmd(t_parse *p, t_cmd *cmd)
{
	char	**envp;

	if (!cmd->cmd)
		return (0);
	if (access(cmd->cmd[0], F_OK) == -1)
	{
		cmd->cmd[0] = search_cmd(p, cmd);
		if (!cmd->cmd[0])
		{
			printf("%s: command not found\n", cmd->s[0]);
			return (127);
		}
	}
	envp = create_envp_tab(p->envp);
	execve(cmd->cmd[0], cmd->cmd, envp);
	clean_2d_tab(envp);
	return (127);
}
