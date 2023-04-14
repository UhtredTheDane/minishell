/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 13:00:43 by lloisel           #+#    #+#             */
/*   Updated: 2023/04/14 23:02:56 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../includes/parsing.h"
#include "../../includes/error.h"
#include <unistd.h>
#include "../../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

void	add_cmd_bis(t_parse *p, t_cmd *cmd)
{
	if (p->first == NULL)
	{
		p->first = cmd;
		p->last = cmd;
	}
	else
	{
		p->last->next = cmd;
		p->last = cmd;
	}
	p->count = p->count + 1;
}

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->s = NULL;
	cmd->cmd = NULL;
	cmd->next = NULL;
	cmd->filename_out = NULL;
	cmd->filename_in = NULL;
	cmd->in = -1;
	cmd->out = -1;
	cmd->append = 1;
	cmd->heredoc = 0;
	cmd->pipe_heredoc = NULL;
	return (cmd);
}

int	add_cmd(t_parse *p, int start, int end)
{
	t_cmd	*cmd;
	int		size;
	int		i;

	cmd = init_cmd();
	if (!cmd)
		return (0);
	size = end - start;
	if (size <= 0 && p->s[start] != '\0')
		return (free(cmd), error("Syntax error Unexpected token : '|'\n"), 0);
	cmd->s = malloc(sizeof(char *));
	if (!cmd->s)
		return (0);
	cmd->s[0] = malloc(sizeof(char) * size + 1);
	if (!cmd->s[0])
		return (0);
	i = -1;
	while (++i < size)
		cmd->s[0][i] = p->s[start + i];
	cmd->s[0][i] = '\0';
	add_cmd_bis(p, cmd);
	return (1);
}

t_parse	*init_parse(t_envp *envp_dico)
{
	t_parse	*p;

	p = malloc(sizeof(t_parse));
	if (!p)
		return (NULL);
	p->s = NULL;
	p->pipes_fd = NULL;
	p->envp = envp_dico;
	p->count = 0;
	p->first = NULL;
	p->last = NULL;
	return (p);
}
