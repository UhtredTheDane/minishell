/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:25:39 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/14 21:15:31 by agengemb         ###   ########.fr       */
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
		*current_pos = skip_to_x(cmd, *current_pos, first);
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
		quote_pos = skip_to_x(trim_cmd, current_pos, "'");
		double_pos = skip_to_x(trim_cmd, current_pos, "\"");
		trim_cmd = rm_first(trim_cmd, &current_pos, quote_pos, double_pos);
		if (!trim_cmd)
			return (cmd);
	}
	free(cmd);
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

int	already_with_path(t_parse *p, char *cmd)
{
	char	**all_path;
	size_t	i;
	size_t	size;

	if (cmd[0] == '.' && cmd[1] == '/')
		return (1);	
	all_path = ft_split(get_value(p->envp, "PATH"), ':');
	if (!all_path)
		return (0);
	i = 0;
	while (all_path[i])
	{
		size = ft_strlen(all_path[i]);
		if (ft_strncmp(all_path[i], cmd, size) == 0)
		{
			clean_2d_tab(all_path);
			return (1);	
		}
		++i;
	}
	clean_2d_tab(all_path);
	return (0);
}

int	run_cmd(t_parse *p, t_cmd *cmd)
{
	char	**envp;
	char	*tempo_cmd;

	if (!cmd->cmd)
		return (0);
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
	if (access(cmd->cmd[0], F_OK) == -1)
	{
		printf("minishell: %s: No such file or directory\n", cmd->cmd[0]);
		return (127);
	}
	if (access(cmd->cmd[0], X_OK) == -1)
	{
		printf("minishell: %s: Permission denied\n", cmd->cmd[0]);
		return (126);
	}
	envp = create_envp_tab(p->envp);
	execve(cmd->cmd[0], cmd->cmd, envp);
	clean_2d_tab(envp);
	return (127);
}
