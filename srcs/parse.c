/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:17:21 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/16 12:09:51 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../includes/parsing.h"

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
	//	printf("%s\n",p->last->s);
}

t_cmd *init_cmd(void)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	if(!cmd)
		return(NULL);
	cmd->s = NULL;
	cmd->cmd = NULL;
	cmd->next = NULL;
	cmd->filename_out = NULL;
	cmd->filename_in = NULL;
	cmd->in = -1;
	cmd->out = -1;
	cmd->append = 0;
	//bzero(cmd,sizeof (t_cmd));
	return (cmd);
}

int add_cmd(t_parse *p ,int start,int end)
{
	t_cmd *cmd;
	cmd = init_cmd();
	int size;
	size  = end-start;
	//printf("%d\n",size);
	if(size <= 0 && p->s[start] != '\0')
		return(0);
	cmd->s = malloc(sizeof(char)*size + 1);
	if(!cmd->s)
		return(0);
	int i;
	i = 0;
	while(i < size)
	{	
		cmd->s[i]=p->s[start + i];
		++i;
	}
	cmd->s[i] = '\0';
	//printf("%s\n",cmd->s);
	add_cmd_bis(p,cmd);
	p->count = p->count + 1;
	return(1);
}
t_parse *init_parse(void)
{
	t_parse *p;

	p = malloc(sizeof(t_parse));
	if(!p)
		return(NULL);
	p->s = NULL;
	p->envp = NULL;
	p->count  = 0;
	p->first = NULL;
	p->last = NULL;
	return(p);
}

int parse(char *input,t_parse *p)
{
	int i;
	int start_w;

	i = 0;
	start_w = 0;
	p->s = input;
	while(p->s[i] && p->s[i] != '\0')
	{
		if(p->s[i] == '|')
		{	
			if(!add_cmd(p,start_w,i))
				return(0);
			start_w = i + 1;
		}
		if(p->s[i] == '\'')
		{
			++i;
			while(p->s[i] != '\0' && p->s[i] !='\'')
				++i;
			if(p->s[i] == '\0')
				return(0);
		}
		if(p->s[i] == '"')
		{
			++i;
			while(p->s[i] != '\0' && p->s[i] !='"')
				++i;
			if(p->s[i] == '\0')
				return(0);
		}
		++i;
	}
	if(!add_cmd(p,start_w,i))
		return(0);
	return(1);
}

t_parse *parsing(char *input)
{
	t_parse *p;

	p = init_parse();
	if(!p)
		return(NULL);
	if(!parse(input,p))
		return (NULL);
	return (p);
	/*else 
	{
		printf("count :%d\n",p->count);	
		t_cmd *current;
		printf("printf all : \n");
		current = p->first;

		while(current)
		{
			printf("%s\n",current->s);
			current = current->next;
		}
	}*/
}
