/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdinout.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:07:38 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/26 14:59:15 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"	
#include <string.h>
#include <stdio.h>
#include <stdlib.h>		
#include "../../libft/libft.h"

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
int handle_file(t_cmd *cmd)
{
	int fd;

	fd = open(cmd->filename_out,O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		printf("minishell: %s: Is a directory",cmd->filename_out);
		return (0);
	}
	if(cmd->append)
	{
		fd = open(cmd->filename_out,O_WRONLY | O_CREAT | O_APPEND,0644);
		if(fd < 0 )
			return(0);
		close(fd);
	}
	else
	{
		unlink(cmd->filename_out);
		fd = open(cmd->filename_out,O_WRONLY | O_CREAT ,0644);
		if(fd < 0 )
			return(0);
		close(fd);
	}
	return(1);
}
char *trimming(int op,t_cmd *cmd,int start,int end)
{
	char	*name;
	char	*tmp;
	int		size;
	int		i;

	i = -1;
	size = end-start;
	if(size <= 0)
		return(NULL);
	name = malloc(sizeof(char)* (size)+1);
	while(++i < size)
		name[i] = cmd->s[0][start + i];
	name[i] ='\0';
	cmd->s[0][op] = '\0';
	size  = (ft_strlen(cmd->s[0]) + ft_strlen(cmd->s[0] + end)) + 1; 
	tmp = malloc(size);
	if(!tmp)
		return(NULL);	
	tmp[0] = '\0';
	ft_strlcpy(tmp ,cmd->s[0], size);
	ft_strlcat(tmp,cmd->s[0] + end, size);
	free(cmd->s[0]);
	cmd->s[0] = tmp;
	return(name);
}

int fill_stdout(t_cmd *cmd,int i)
{
	int start_w;
	int op;	

	op = i;
	++i;
	if(cmd->s[0][i] && cmd->s[0][i] == '>')
	{
		cmd->append = 1;
		i++;
	}
	else 
		cmd->append = 0;
	i = skip_space(cmd->s[0],i);
	if(is_special(cmd->s[0][i],"<>\0 "))
		return(0);
	start_w = i;
	while(cmd->s[0][i] && !is_special(cmd->s[0][i],"<> "))
	{
		if(cmd->s[0][i] == '\'')
			i = skip_to_X(cmd->s[0],i,"\'");
		else if(cmd->s[0][i] == '\"')
			i = skip_to_X(cmd->s[0],i,"\"");
		i++;
	}
	if(is_special(cmd->s[0][i],"<> ") && start_w == i)
		return(0);
	cmd->filename_out = trimming(op,cmd,start_w,i);
	handle_file(cmd);
	return(1);
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
	char *tmp;
	
	op = i;	
	i++;
	if(cmd->s[0][i] && cmd->s[0][i] == '<')
	{
		tmp = here_doc(cmd,i + 1,op);
		if(!tmp)
			return(0);
		cmd->heredoc = 1;
		if(!cmd->value_hd)
			cmd->value_hd = tmp;
		else
		{
			free(cmd->value_hd);
			cmd->value_hd = tmp;
		}
	}
	else
	{
		if(!simple_stdin(cmd,i,op))
			return (0);
		cmd->heredoc = 0;
	}	
	return(1);
}
