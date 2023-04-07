/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:25:39 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/07 16:30:36 by agengemb         ###   ########.fr       */
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

char	*remove_first(char *cmd, int *current_pos, int quote_pos, int double_pos)
{
	char	*first;
	char	*tempo_str;

	first = init_pos_first(current_pos, quote_pos, double_pos);
	if ((size_t) *current_pos != ft_strlen(cmd))
	{
		cmd[*current_pos] = '\0';
		tempo_str = ft_strjoin(cmd, cmd + *current_pos + 1);
		free(cmd);
		cmd = tempo_str;
		*current_pos = skip_to_X(cmd, *current_pos, first);
		cmd[*current_pos] = '\0';
		tempo_str = ft_strjoin(cmd, cmd + *current_pos + 1);
		free(cmd);
		cmd = tempo_str;
	}
	return (cmd);
}

char	*trim_quotes(char *cmd)
{
	char	*res;
	int		current_pos;
	int		quote_pos;
	int		double_pos;

	current_pos = 0;
	res = cmd;
	while (cmd[current_pos])
	{
		quote_pos = skip_to_X(res, current_pos, "'");
		double_pos = skip_to_X(res, current_pos, "\"");
		res = remove_first(res, &current_pos, quote_pos, double_pos);
	}
	return (res);
}

void	prepare_cmd(t_cmd *cmd)
{
	size_t	i;

	if (cmd->heredoc)
	{
		if (ft_strncmp(cmd->cmd[0], "grep", 4) == 0)
			cmd->cmd = update_for_grep(cmd->cmd);
	}
	i = 0;
	while (cmd->cmd[i])
	{
		cmd->cmd[i] = trim_quotes(cmd->cmd[i]);
		++i;
	}
}

int	run_cmd(t_parse *p, t_cmd *cmd)
{
	if (access(cmd->cmd[0], F_OK) == -1)
	{
		cmd->cmd[0] = search_cmd(p, cmd);
		if (!cmd->cmd[0])
		{
			//free
			printf("%s: command not found\n",cmd->s[0]);
			return (127);
		}
	}
	execve(cmd->cmd[0], cmd->cmd, create_envp_tab(p->envp));
	return (127);
}
