/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 13:00:43 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/27 21:32:58 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../includes/parsing.h"
#include <unistd.h>
#include "../../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

void add_cmd_bis(t_parse *p,t_cmd *cmd)
{
	if(p->first == NULL)
	{
		p->first = cmd;	
		p->last = cmd;	
	}
	else
	{
		p->last->next = cmd;
		p->last = cmd;
	}
}

t_cmd *init_cmd(void)
{
	t_cmd *cmd;

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
	return (cmd);
}

int add_cmd(t_parse *p ,int start,int end)
{
	t_cmd *cmd;
	int size;
	int i;

	cmd = init_cmd();
	if(!cmd)
		return(0);
	size  = end-start;
	if(size <= 0 && p->s[start] != '\0')
		return(0);
	cmd->s = malloc(sizeof(char *));
	if(!cmd->s)
		return (0);
	cmd->s[0] = malloc(sizeof(char)*size + 1);
	if(!cmd->s[0])
		return(0);
	i = 0;
	while(i < size)
	{	
		cmd->s[0][i]=p->s[start + i];
		++i;
	}
	cmd->s[0][i] = '\0';
	add_cmd_bis(p,cmd);
	p->count = p->count + 1;
	return(1);
}

t_parse *init_parse(t_envp *envp_dico, struct sigaction *old_action)
{
	t_parse *p;

	p = malloc(sizeof(t_parse));
	if(!p)
		return(NULL);
	p->s = NULL;
	p->envp = envp_dico;
	p->count  = 0;
	p->first = NULL;
	p->last = NULL;
	return (p);
}

