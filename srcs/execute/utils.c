/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:31:04 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/07 16:34:19 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	char_in_str(char c, char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		++i;
	}
	return (0);
}

void	add_option_a(char **cmd, char **new_cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (j == 1)
			new_cmd[j] = ft_strdup("-a");
			//tester pour free
		else
		{
			new_cmd[j] = ft_strdup(cmd[i]);
			//tester poour free en cas d erreur
			++i;
		}
		++j;
	}
	new_cmd[j] = NULL;
}

char	**update_for_grep(char **cmd)
{
	char	**new_cmd;
	int		i;

	i = 0;
	while (cmd[i])
		i++;
	new_cmd = malloc(sizeof(char *) * (i + 2));
	if (!new_cmd)
		return (cmd);
	add_option_a(cmd, new_cmd);
	//if !new_cmd
	//free(cmd);
	return (new_cmd);
}

int	redirect_stdin(t_parse *p, t_cmd *cmd, int num_read)
{
	if (cmd->heredoc)
	{
		dup2(cmd->pipe_heredoc[0], 0);
		close(cmd->pipe_heredoc[0]);
	}
	else if (cmd->filename_in)
	{
		cmd->in = open(cmd->filename_in, O_RDONLY);
		dup2(cmd->in, 0);
		close(cmd->in);
	}
	else
		if (!link_stdin(p, num_read))
			return (0);
	return (1);
}

int	redirect_stdout(t_parse *p, t_cmd *cmd, int num_write)
{
	int	flags;

	if (cmd->filename_out)
	{
		flags = O_WRONLY | O_CREAT;
		if (cmd->append)
			flags = flags | O_APPEND;
		else
			flags = flags | O_TRUNC;
		cmd->out = open(cmd->filename_out, flags,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		dup2(cmd->out, 1);
		close(cmd->out);
	}
	else
		if (!link_stdout(p, num_write))
			return (0);
	return (1);
}
