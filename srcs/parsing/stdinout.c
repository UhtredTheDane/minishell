/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdinout.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:07:38 by lloisel           #+#    #+#             */
/*   Updated: 2023/04/14 17:40:59 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"	
#include "../../includes/error.h"	
#include <string.h>
#include <stdio.h>
#include <stdlib.h>		
#include "../../libft/libft.h"

int	handle_file(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->filename_out, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		printf("minishell: %s: Is a directory\n", cmd->filename_out);
		return (0);
	}
	if (cmd->append)
	{
		fd = open(cmd->filename_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			return (0);
		close(fd);
	}
	else
	{
		unlink(cmd->filename_out);
		fd = open(cmd->filename_out, O_WRONLY | O_CREAT, 0644);
		if (fd < 0)
			return (0);
		close(fd);
	}
	return (1);
}

int	fill_out_bis(t_cmd *cmd, int i)
{
	while (cmd->s[0][i] && !is_special(cmd->s[0][i], "<> "))
	{
		if (cmd->s[0][i] == '\'')
			i = skip_to_x(cmd->s[0], i, "\'");
		else if (cmd->s[0][i] == '\"')
			i = skip_to_x(cmd->s[0], i, "\"");
		i++;
	}
	return (i);
}

int	fill_stdout(t_cmd *cmd, int i)
{
	int	start_w;
	int	op;	

	op = i;
	++i;
	if (cmd->s[0][i] && cmd->s[0][i] == '>')
	{
		cmd->append = 1;
		i++;
	}
	else
		cmd->append = 0;
	i = skip_space(cmd->s[0], i);
	if (!cmd->s[0][i] || is_special(cmd->s[0][i], "<> |"))
		return (syntax_err(cmd->s[0] + i, cmd), 0);
	start_w = i;
	i = fill_out_bis(cmd, i);
	if (is_special(cmd->s[0][i], "<> ") && start_w == i)
		return (syntax_err(cmd->s[0] + i, cmd), 0);
	if(cmd->filename_out)
		free(cmd->filename_out);	
	cmd->filename_out = trimming(op, cmd, start_w, i);
	return (handle_file(cmd));
}

int	simple_stdin(t_cmd *cmd, int i, int op)
{
	char *tmp;

	tmp = get_name(cmd, i, op);
	if(cmd->filename_in)
		free(cmd->filename_in);
	cmd->filename_in = tmp;
	if (!cmd->filename_in)
		return (0);
	return (1);
}

int	fill_stdin(t_parse *p, t_cmd *cmd, int i)
{
	int	op;
	int	tmp;

	op = i;
	i++;
	if (cmd->s[0][i] && cmd->s[0][i] == '<')
	{
		tmp = here_doc(p, cmd, i + 1, op);
		if (!tmp)
			return (0);
		cmd->heredoc = 1;
	}
	else
	{
		if (!simple_stdin(cmd, i, op))
			return (0);
		cmd->heredoc = 0;
	}
	return (1);
}
