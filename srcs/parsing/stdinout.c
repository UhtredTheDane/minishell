/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdinout.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:07:38 by lloisel           #+#    #+#             */
/*   Updated: 2023/04/17 20:00:44 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"	
#include "../../includes/error.h"	
#include <string.h>
#include <stdio.h>
#include <stdlib.h>		
#include "../../libft/libft.h"

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

int	fill_stdout(t_cmd *cmd, int i, t_envp *envp)
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
		return (syntax_err(cmd->s[0] + i, cmd), 2);
	start_w = i;
	i = fill_out_bis(cmd, i);
	if (is_special(cmd->s[0][i], "<> ") && start_w == i)
		return (syntax_err(cmd->s[0] + i, cmd), 2);
	if (cmd->filename_out)
		free(cmd->filename_out);
	cmd->filename_out = trimming(op, cmd, start_w, i);
	return (handle_file(cmd, envp));
}

int	simple_stdin(t_cmd *cmd, int i, int op, t_envp *envp)
{
	char	*tmp;

	tmp = get_name(cmd, i, op);
	if (!tmp)
		return (2);
	if (cmd->filename_in)
		free(cmd->filename_in);
	tmp = replace_dollards_string(tmp, 0, envp);
	cmd->filename_in = trim_quotes(tmp);
	free(tmp);
	if (!cmd->filename_in)
		return (1);
	return (handle_file_stdin(cmd));
}

int	fill_stdin(t_parse *p, t_cmd *cmd, int i, t_envp *envp)
{
	int	op;
	int	tmp;

	op = i;
	i++;
	if (cmd->s[0][i] && cmd->s[0][i] == '<')
	{
		tmp = here_doc(p, cmd, i + 1, op);
		if (tmp != 0)
			return (tmp);
		cmd->heredoc = 1;
	}
	else
	{
		tmp = simple_stdin(cmd, i, op, envp);
		if (tmp)
			return (tmp);
		cmd->heredoc = 0;
	}
	return (0);
}
