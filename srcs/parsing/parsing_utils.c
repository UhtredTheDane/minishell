/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 12:53:06 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/25 17:40:44 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"
#include "../../includes/parsing.h"
#include "../../libft/libft.h"
#include "../../includes/envp.h"
#include <stdio.h>


void display_cmd(t_cmd *cmd)
{
	printf("  String : %s\n",cmd->s[0]);
	printf("  In : %d\n  Out : %d\n",cmd->in,cmd->out);
	printf("  Filename in : %s \n",cmd->filename_in);
	printf("  Filename out : %s \n",cmd->filename_out);
	printf("  Append : %d\n",cmd->append);
	printf("  Heredoc value  : %s\n",cmd->value_hd);
	printf("  Heredocboolean : %d\n",cmd->heredoc);
	int i;
	i=0;
	if(cmd->cmd)
	{
		printf("  CMD TAB : \n");
		while(cmd->cmd[i] != NULL)
		{
			printf("  |%s|\n",cmd->cmd[i]);
			++i;
		}
	}
	printf("-------------------\n");
}

void display_parse(t_parse *p)
{
	t_cmd *current;
	int i = 1;

	current=p->first;
	printf("------ PARSE ------\n");
	printf("  String : %s\n",p->s);
	printf("  Count : %d\n\n",p->count);
	while(current)
	{
		printf("------ CMD %i ------\n",i);
		display_cmd(current);
		current = current->next;
		++i; 
	}
	printf("\n");
}

int skip_space(char *s,int i)
{
	while(s[i] && is_special(s[i]," "))
		i++;	
	return (i);
}

int skip_to_X(char *s,int i,char *charset)
{
	while(s[i] && !is_special(s[i],charset))
		i++;
	return(i);
}
