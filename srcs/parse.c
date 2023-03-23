/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:17:21 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/23 20:02:19 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../includes/parsing.h"
#include <unistd.h>
#include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>


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
	if (!cmd)
		return (NULL);
	cmd->s = NULL;
	cmd->cmd = NULL;
	cmd->next = NULL;
	cmd->filename_out = NULL;
	cmd->filename_in = NULL;
	cmd->in = -1;
	cmd->out = -1;
	cmd->append = 0;
	return (cmd);
}

int add_cmd(t_parse *p ,int start,int end)
{
	t_cmd *cmd;
	int size;
	int i;

	cmd = malloc(sizeof(t_cmd));
	if(!cmd)
		return(0);
	bzero(cmd,sizeof (t_cmd));
	size  = end-start;
	if(size <= 0 && p->s[start] != '\0')
		return(0);
	cmd->s = malloc(sizeof(char)*size + 1);
	if(!cmd->s)
		return(0);
	i = 0;
	while(i < size)
	{	
		cmd->s[i]=p->s[start + i];
		++i;
	}
	cmd->s[i] = '\0';
	add_cmd_bis(p,cmd);
	p->count = p->count + 1;
	return(1);
}

t_parse *init_parse(t_envp *envp_dico)
{
	t_parse *p;

	p = malloc(sizeof(t_parse));
	if(!p)
		return(NULL);
	p->s = NULL;
	p->envp = envp_dico;
	p->count  = 0;
	p->first = NULL;
	p->last = NULL;
	return (p);
}


int single_quote_no_close(char *s,int *i)
{
	*i = *i + 1;
	while(s[*i] != '\0' && s[*i] !='\'')
		*i = *i +1;
	if(s[*i] == '\0')
		return(1);
	return(0);
}

int double_quote_no_close(char *s,int *i)
{
	*i = *i + 1;
	while(s[*i] != '\0' && s[*i] !='\"')
		*i = *i +1;
	if(s[*i] == '\0')
		return(1);
	return(0);
}

int pipe_at_end(t_parse *p)
{
	char *input;
	char *tmp;
	int size;

	input = readline("pipe>");
	tmp = p->s;
	size  = ft_strlen(input) + ft_strlen(p->s) + 1;
	p->s = malloc(sizeof(char)*size);
	if(!p->s)
		return (0);
	p->s[0] = '\0';
	ft_strlcat(p->s,tmp,size);
	ft_strlcat(p->s,input,size);
	free(tmp);
	return(1);	
}
int parse_bis(t_parse *p,int *i,int *start_w)
{
	if(p->s[*i] == '|')
	{
		if(!add_cmd(p,*start_w,*i))
			return(0);
		*start_w = *i + 1;
		*i = skip_space(p->s,*i + 1);
		if(p->s[*i] == '\0')
		{
			if(!pipe_at_end(p))
				return(0);
		}	
	}
	if(p->s[*i] == '\'')
	{
		if(single_quote_no_close(p->s,i))	
			return(0);
	}
	if(p->s[*i] == '\"')
	{
		if(double_quote_no_close(p->s,i))	
			return(0);
	}
	return(1);
}

int parse(char *input,t_parse *p)
{
	int i;
	int start_w;

	i = -1;
	start_w = 0;
	p->s = input;
	while(p->s[++i] && p->s[i] != '\0')
	{
		if(!parse_bis(p,&i,&start_w))
			return(0);
	}
	if(!add_cmd(p,start_w,i))
		return(0);
	return(1);
}

t_parse *parsing(char *input, t_envp *envp_dico)
{
	t_parse *p;
	int	i;

	p = init_parse(envp_dico);
	if(!p)
		return(0);
	if(!parse(input,p))
		return (NULL);
	if (p->count < 2)
		p->pipes_fd = NULL;
	else
	{
		p->pipes_fd = malloc(sizeof(int) * (p->count - 1) * 2);
		if (!p->pipes_fd)
			return (NULL);
	}
	i = 0;
	while (i < (p->count - 1) * 2)
	{
		if (pipe(p->pipes_fd + i) == -1)
		{
			/*config->pipes_nb = i / 2;
			  close_all_pipes(config);
			  free(config->pipes_fd);
			  return (0);*/
		}
		i += 2;
	}
	return (p);	
}
