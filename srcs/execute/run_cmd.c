/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:25:39 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/16 02:39:53 by agengemb         ###   ########.fr       */
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

char	*rm_couple(char *cmd, int *current_pos, int quote_pos, int double_pos)
{
	char	*first;
	char	*tempo_str;
	int		i;

	tempo_str = NULL;
	first = init_pos_first(current_pos, quote_pos, double_pos);
	i = 0;
	while (i < 2)
	{
		if (cmd[*current_pos])
		{
			cmd[*current_pos] = '\0';
			tempo_str = ft_strjoin(cmd, cmd + *current_pos + 1);
			if (!tempo_str)
				return (NULL);
			free(cmd);
			cmd = tempo_str;
		}
		if (!i)
			*current_pos = skip_to_x(cmd, *current_pos, first);
		++i;
	}
	if (!tempo_str)
		free(cmd);
	return (tempo_str);
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
		quote_pos = skip_to_x(trim_cmd, current_pos, "'");
		double_pos = skip_to_x(trim_cmd, current_pos, "\"");
		if (quote_pos != double_pos)
		{
			trim_cmd = rm_couple(trim_cmd, &current_pos, quote_pos, double_pos);
			if (!trim_cmd)
				return (NULL);
		}
		else
		{
			current_pos = quote_pos;
		}
	}
	return (trim_cmd);
}

void	prepare_cmd(t_cmd *cmd)
{
	size_t	i;
	char	*tempo_cmd;

	i = 0;
	if (cmd->cmd)
	{
		if (cmd->heredoc && ft_strncmp(cmd->cmd[0], "grep", 4) == 0)
			cmd->cmd = update_for_grep(cmd->cmd);
		while (cmd->cmd[i])
		{
			tempo_cmd = trim_quotes(cmd->cmd[i]);
			if (tempo_cmd)
			{
				free(cmd->cmd[i]);
				cmd->cmd[i] = tempo_cmd;
			}
			++i;
		}
	}
}

int	run_cmd(t_parse *p, t_cmd *cmd)
{
	char	**envp;
	char	*tempo_cmd;
	int		res_test;

	res_test = first_test(cmd->cmd);
	if (res_test != 1)
		return (res_test);
	if (!already_with_path(p, cmd->cmd[0]))
	{
		tempo_cmd = search_cmd(p, cmd);
		if (!tempo_cmd)
		{
			printf("%s: command not found\n", cmd->s[0]);
			return (127);
		}
		cmd->cmd[0] = tempo_cmd;
	}
	res_test = test_acces(cmd);
	if (res_test)
		return (res_test);
	envp = create_envp_tab(p->envp);
	execve(cmd->cmd[0], cmd->cmd, envp);
	clean_2d_tab(envp);
	return (127);
}
