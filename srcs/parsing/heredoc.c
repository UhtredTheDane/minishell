/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:47:53 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/26 22:53:31 by agengemb         ###   ########.fr       */
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

char *get_heredoc(t_cmd* cmd, char *word)
{
	char *value;
	char *input;
	char *tmp;
	int size;

	cmd->pipe_heredoc = malloc(sizeof(int) * 2);
	if (!cmd->pipe_heredoc)
			return (NULL);
	if (pipe(cmd->pipe_heredoc) == -1)
	{
		free(cmd->pipe_heredoc);
		return (NULL);
	}
	
	input = readline("Heredoc>");
	tmp = "";
	value = "";
	while(input && strncmp(input, word, max(input, word)))
	{
		size = ft_strlen(input) + ft_strlen(value) + 2; 
		value = malloc(size);
		if(!value)
		{
			close(cmd->pipe_heredoc[0]);
			close(cmd->pipe_heredoc[1]);
			return(NULL);	
		}
		value[0] = '\0';
		ft_strlcat(value, tmp, size);
		if(tmp && *tmp)
			free(tmp);
		tmp = value;
		ft_strlcat(value, input, size);
		ft_strlcat(value,"\n",size);
		

		write(cmd->pipe_heredoc[1], value, size);
		
		input = readline("Heredoc>");
	}
	if(!input)
	{
		printf("Heredoc expect %s not end of file",word);
		close(cmd->pipe_heredoc[0]);
		close(cmd->pipe_heredoc[1]);
		return(NULL);
	}
	close(cmd->pipe_heredoc[1]);
	return (value);	
}

char *here_doc(t_cmd *cmd,int i,int op)
{
	char *word;
	int j;
	
	j = 0;
	word = get_name(cmd,i,op);
	if(!word)
		return(NULL);
	printf("cmd %s\n", cmd->cmd[0]);
	if (ft_strncmp(cmd->cmd[0], "grep", 4) == 0)
	{
		while(cmd->cmd[j])
			++j;
		cmd->cmd[j] = malloc(sizeof(char) * 3);
		if (!cmd->cmd[j])
		{
			free(word);
			return (NULL);
		}
		cmd->cmd[j][0] = '-';
		cmd->cmd[j][1] = 'a';
		cmd->cmd[j][2] = '\0';
	}
	return (get_heredoc(cmd, word));
}
