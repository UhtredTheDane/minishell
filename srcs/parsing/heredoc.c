/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:47:53 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/26 16:46:04 by lloisel          ###   ########.fr       */
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

	int flags; = O_WRONLY | O_CREAT | O_TRUNC;
	int fd_heredoc; 
	
	flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd_heredoc = open("heredoc", flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (fd_heredoc == -1)
		return (NULL);



	input = readline("Heredoc>");
	tmp = "";
	value = "";
	while(input && strncmp(input, word, max(input, word)))
	{
		size = ft_strlen(input) + ft_strlen(value) + 2; 
		value = malloc(size);
		if(!value)
		{
			close(fd_heredoc);
			unlink("heredoc");
			return(NULL);	
		}
		value[0] = '\0';
		ft_strlcat(value, tmp, size);
		if(tmp && *tmp)
			free(tmp);
		tmp = value;
		ft_strlcat(value, input, size);
		ft_strlcat(value,"\n",size);
		

		write(fd_heredoc, value, size);
		
		input = readline("Heredoc>");
	}
	if(!input)
	{
		printf("Heredoc expect %s not end of file",word);
		close(fd_heredoc);
		unlink("heredoc");
		return(NULL);
	}
	close(fd_heredoc);
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
