/*                                                        :::      ::::::::   */
/*   edit_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:59:11 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/16 14:47:19 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../includes/parsing.h"
#include "../libft/libft.h"
#include "../includes/envp.h"
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
	printf("s : %s i : %d\n",s + *i,*i);
	while(s[*i] && !is_special(s[*i]," "))
	{
		if(s[*i] == '\'')
			*i = skip_to_X(s,*i + 1,"\'") + 1;	
		if(s[*i] == '\"')
			*i = skip_to_X(s,*i + 1,"\"") + 1;	
		if(s[*i])
			*i = skip_to_X(s,*i,"\"\' ");	
	}	
	printf("s : %s i : %d\n",s + *i ,*i);
	size = *i - size;
	printf("%d\n",size);
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
		i = skip_space(s,i);	
		while(s[i] && !is_special(s[i]," "))
		{
			if(s[i] == '\'')
				i = skip_to_X(s,i + 1,"\'") + 1;	
			if(s[i] == '\"')
				i = skip_to_X(s,i + 1,"\"") + 1;	
			if(s[i])
				i = skip_to_X(s,i,"\"\' ");	
		}
		count++;
		i++;
	}
	printf("%d Word\n",count);
	return(count);
}
char **create_tab(char *s,int size)
{
	int i;
	int size_w;
	char **tmp;
	int nb;

	nb = 0;
	i = 0 ;	
	i = skip_space(s,i);
	if(s[i] == '\0')
		return(NULL);
	tmp = malloc(sizeof(char*)*size + 1);
	if(!tmp)
		return(NULL);
	tmp[size] = NULL;	
	while(s[i])
	{
		i = skip_space(s,i);	
		size_w = to_word_end(s,&i);
		printf("size_w : %d \n",size_w);
		tmp[nb] = malloc(sizeof(char)*size_w + 1);
		/*if(!tmp[i])
			return(clean_2d_tab(tmp),NULL);	*/
		ft_strlcat(tmp[nb],s + i - size_w ,size_w + 1);
		i++;
		nb++;
	}
	return(tmp);
}

int split_cmd(t_parse *p)
{
	t_cmd *current;

	current = p->first;	
	while(current)
	{
		//printf("|%s| : %d\n",current->s,size_of_tab(current->s));
		current->cmd = create_tab(current->s,size_of_tab(current->s));
		current = current->next;
	}
	return(1);
}

void display_cmd(t_cmd *cmd)
{
	printf("  String : %s\n",cmd->s);
	printf("  In : %d\n  Out : %d\n",cmd->in,cmd->out);
	printf("  Filename in : %s \n",cmd->filename_in);
	printf("  Filename out : %s \n",cmd->filename_out);
	printf("  Append : %d\n",cmd->append);
	int i;
	i=0;
	if(cmd->cmd)
	{
		printf("  CMD TAB : \n");
		while(cmd->cmd[i])
		{
			printf("  %s\n",cmd->cmd[i]);
			++i;
		}
	}
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

int edit_parsing(t_parse *p)
{
	t_cmd *current;
	int i;
	char c;

	current = p->first;
	while(current)
	{
		i = 0;
		while(current->s[i])
		{
			if(current->s[i] == '\'')		
			{
				i++;
				while(current->s[i] && current->s[i] != '\'')
					i++;
			}			
			if(current->s[i] == '\"')
			{
				i++;
				while(current->s[i] && current->s[i] != '\"')
						i++;
			}	
			if(current->s[i] == '<')
			{
				if(!fill_stdin(current,i))
					return(0);
			}
			if(current->s[i] == '>')
			{
				if(!fill_stdout(current,i))
					return(0);		
			}
			c = current->s[i];
			if(c !='<' && c!='>')
				i++;
		}
		current = current->next;
	}
	return(1);
}
