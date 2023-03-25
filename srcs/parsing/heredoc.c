/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:47:53 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/25 13:36:51 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"	
#include "../../includes/main.h"	
#include <string.h>
#include <stdio.h>
#include <stdlib.h>		
#include "../../libft/libft.h"


char *get_name(t_cmd *cmd,int i,int op)
{
	int start_w;
		
	i = skip_space(cmd->s[0], i);
	if(is_special(cmd->s[0][i],"<> "))
		return(NULL);
	start_w = i;
	while(cmd->s[0][i] && !is_special(cmd->s[0][i],"<> "))
	{
		if(cmd->s[0][i] == '\'')
			i = skip_to_X(cmd->s[0] + i, i + 1,"\'");
		else if(cmd->s[0][i] == '\"')
			i = skip_to_X(cmd->s[0] + i, i + 1,"\"");
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
