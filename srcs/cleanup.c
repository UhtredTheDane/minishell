/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:12:01 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/13 15:32:44 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/pipex.h"

int free_cmd(t_cmd *cmd)
{
	if(cmd->s)
		free(cmd->s);
	if(cmd->cmd)
		clean_2d_tab(cmd->cmd);
	if(cmd->filename_in)
		free(cmd->filename_in);
	if(cmd->filename_out)
		free(cmd->filename_out);
	return(1);
}

int free_parse(t_parse *p)
{
	t_cmd *current;
	t_cmd *tmp;
	
	current = p->first;	
	while(current)
	{
		tmp = current;
		free_cmd(current);
		current = current->next;
		free(tmp);
	}
	free(p);
	return(1);
}
