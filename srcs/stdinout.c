/*                                                        :::      ::::::::   */
/*   stdinout.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:07:38 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/14 18:11:32 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"	
#include <string.h>
#include <stdio.h>
#include <stdlib.h>		
#include "../libft/libft.h"

int is_special(char c,char *charset)
{
	int i;

	i = 0;
	while (charset[i])
	{
		if(charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char *trimming(int op,t_cmd *cmd,int start,int end)
{
	char	*name;
	char	*tmp;
	int		size;
	int		i;

	i = 0;
	size = end-start;
	if(size <= 0)
		return(NULL);
	name = malloc(sizeof(char)* (size)+1);
	while(i < size)
	{
		name[i] = cmd->s[start + i];
		i++;
	}
	name[i] ='\0';
	cmd->s[op] = '\0';
	tmp = cmd->s;
	size  = (ft_strlen(tmp) + ft_strlen(tmp + end)) + 1; 
	cmd->s = malloc(size);
	cmd->s[0] = '\0';
	if(!cmd->s)
		return(NULL);	
	ft_strlcpy(cmd->s ,tmp, size);
	ft_strlcat(cmd->s,tmp + end, size);
	free(tmp);
	return(name);
}

int fill_stdout(t_cmd *cmd,int i)
{
	int start_w;
	int op;	

	op = i;
	i++;
	if(cmd->s[i] && cmd->s[i] == '>')
	{
		cmd->append = 1;
		i++;
	}
	while(cmd->s[i] && cmd->s[i] == ' ')
		i++;

	start_w = i;
	while(cmd->s[i] && !is_special(cmd->s[i],"<> "))
	{
		if(cmd->s[i] == '\'')
		{
			i++;
			while(cmd->s[i] && cmd->s[i] != '\'')
				i++;
		}
		else if(cmd->s[i] == '\"')
		{
			i++;
			while(cmd->s[i] && cmd->s[i] != '\"')
				i++;
		}
		i++;
	}
	if(is_special(cmd->s[i],"<> ") && start_w == i)
		return(0);
	cmd->filename_out = trimming(op,cmd,start_w,i);
	return(1);
}
