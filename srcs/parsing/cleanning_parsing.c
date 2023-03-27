/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanning_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:12:01 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/27 18:17:10 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/pipex.h"

void	clean_2d_tab(char **tab_2d)
{
	size_t	i;

	i = 0;
	while (tab_2d[i])
	{
		if (tab_2d[i])
			free(tab_2d[i]);
		++i;
	}
	free(tab_2d);
}

void free_cmd(t_cmd *cmd)
{
	if(cmd->s)
	{
		if(cmd->s[0])
			free(cmd->s[0]);
		free(cmd->s);
	}
	if(cmd->cmd)
		clean_2d_tab(cmd->cmd);
	if(cmd->filename_in)
		free(cmd->filename_in);
	if(cmd->filename_out)
		free(cmd->filename_out);
}

void free_parse(t_parse *p)
{
	t_cmd *current;
	t_cmd *tmp;

	if(p)
	{	
		current = p->first;	
		while(current)
		{
			tmp = current->next;
			free_cmd(current);
			free(current);
			current = tmp;
		}
		if(p->pipes_fd)
			free(p->pipes_fd);
		free(p);
	}
}
