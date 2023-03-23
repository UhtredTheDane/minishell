/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:47:53 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/23 19:18:46 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"	
#include "../includes/main.h"	
#include <string.h>
#include <stdio.h>
#include <stdlib.h>		
#include "../libft/libft.h"


char *get_name(t_cmd *cmd,int i,int op)
{
	int start_w;
		
	i = skip_space(cmd->s, i);
	if(is_special(cmd->s[i],"<> "))
		return(NULL);
	start_w = i;
	while(cmd->s[i] && !is_special(cmd->s[i],"<> "))
	{
		if(cmd->s[i] == '\'')
			i = skip_to_X(cmd->s + i, i + 1,"\'");
		else if(cmd->s[i] == '\"')
			i = skip_to_X(cmd->s + i, i + 1,"\"");
		i++;
	}
	return(trimming(op,cmd, start_w, i));
}
int max(char *input,char *word)
{
	if(ft_strlen(input) > ft_strlen((word)))
		return(ft_strlen(input));
	return (ft_strlen(word));
}

char *get_heredoc(char *word)
{
	char *value;
	char *input;
	char *tmp;
	int size;

	input = readline("Heredoc>");
	tmp = "";
	value = "";
	while(strncmp(input,word,max(input,word)))
	{
		size = ft_strlen(input)+ft_strlen(value) + 2; 
		value = malloc(size);
		if(!value)
			return(NULL);	
		value[0] = '\0';
		ft_strlcat(value,tmp,size);
		if(tmp && *tmp)
			free(tmp);
		tmp = value;
		ft_strlcat(value,input,size);
		ft_strlcat(value,"\n",size);
		input = readline("Heredoc>");
	}
	return (value);	
}
char *here_doc(t_cmd *cmd,int i,int op)
{
	char *word;
	
	word = get_name(cmd,i,op);
	if(!word)
		return(NULL);
	return (get_heredoc(word));
}

int simple_stdin(t_cmd * cmd , int i,int op)
{
		
	cmd->filename_in = get_name(cmd,i,op);
	if(!cmd->filename_in)
		return(0);
	return(1);
}

int fill_stdin(t_cmd *cmd,int i)
{
	int op;	

	op = i;	
	i++;
	if(cmd->s[i] && cmd->s[i] == '<')
	{	
		if(!here_doc(cmd,i + 1,op))
			return(0);
	}
	else
	{
		if(!simple_stdin(cmd,i,op))
			return (0);
	}	
	return(1);
}
