/*                                                        :::      ::::::::   */
/*   edit_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:59:11 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/16 14:47:19 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"
#include "../../includes/parsing.h"
#include "../../libft/libft.h"
#include "../../includes/envp.h"
#include <stdio.h>

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

int to_word_end(char *s,int *i)
{	
	int size;

	size = *i;
	while(s[*i] && !is_special(s[*i]," "))
	{
		if(s[*i] == '\'')
			*i = skip_to_X(s,*i + 1,"\'") + 1;	
		if(s[*i] == '\"')
			*i = skip_to_X(s,*i + 1,"\"") + 1;	
		if(s[*i])
			*i = skip_to_X(s,*i,"\"\' ");	
	}	
	size = *i - size;
	return(size);
}

int size_of_tab(char *s)
{
	int i;
	int count;

	count = 0;
	i = 0 ;	
	i = skip_space(s,i);
	if(!s[i])
		return(0);
	while(s[i] != '\0')
	{
		while(s[i] && !is_special(s[i]," "))
		{
			if(s[i] == '\'')
				i = skip_to_X(s,i + 1,"\'") + 1;	
			if(s[i] == '\"')
				i = skip_to_X(s,i + 1,"\"") + 1;	
			if(s[i])
				i = skip_to_X(s,i,"\"\' ");	
		}
		i = skip_space(s,i);	
		count++;
	}
	return(count);
}

int fill_cell(char *s,int *i,char **tmp)
{
	int nb;
	int size_w;

	nb = 0;
	while(s[*i])
	{
		size_w = to_word_end(s,i);
		tmp[nb] = malloc(sizeof(char)*(size_w + 1));
		if(!tmp[nb])
			return(clean_2d_tab(tmp),0);
		ft_strlcpy(tmp[nb],s + *i - size_w ,size_w + 1);
		*i = skip_space(s,*i);	
		nb++;
	}
	return(1);
}

char **create_tab(char *s,int size)
{
	int i;
	char **tmp;

	if(!s)
		return(NULL);	
	i = 0 ;	
	i = skip_space(s,i);
	if(!(*(s + i)))
		return(NULL);	
	tmp = malloc(sizeof(char *)*(size + 1));
	if(!tmp)
		return(NULL);	
	if(!fill_cell(s,&i,tmp))
		return(NULL);
	tmp[size] = NULL;
	return(tmp);
}

int split_cmd(t_parse *p)
{
	t_cmd *current;

	current = p->first;	
	while(current)
	{
		current->cmd = create_tab(current->s[0],size_of_tab(current->s[0]));
		current = current->next;
	}
	return(1);
}

void display_cmd(t_cmd *cmd)
{
	printf("  String : %s\n",cmd->s[0]);
	printf("  In : %d\n  Out : %d\n",cmd->in,cmd->out);
	printf("  Filename in : %s \n",cmd->filename_in);
	printf("  Filename out : %s \n",cmd->filename_out);
	printf("  Append : %d\n",cmd->append);
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

int edit_current(t_cmd *current)
{
	int i;

	i = 0;
	while(current->s[0][i])
	{
		if(current->s[0][i] && current->s[0][i] == '\'')
			i = skip_to_X(current->s[0], i + 1, "\'") + 1;
		if(current->s[0][i] && current->s[0][i] == '\"')
			i = skip_to_X(current->s[0], i + 1, "\"") + 1;
		if(current->s[0][i] && current->s[0][i] == '<')
		{
			if(!fill_stdin(current,i))
				return(0);
		}
		else if(current->s[0][i] && current->s[0][i] == '>')
		{
			if(!fill_stdout(current,i))
				return(0);
		}
		else
			i++;
	}
	return(1);
}

int edit_parsing(t_parse *p)
{
	t_cmd *current;

	current = p->first;
	while(current)
	{
		if(!edit_current(current))
			return (0);
		current = current->next;
	}
	return(1);
}
