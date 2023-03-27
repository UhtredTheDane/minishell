/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:17:21 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/26 17:09:41 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../includes/parsing.h"
#include <unistd.h>
#include "../../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

int pipe_at_end(t_parse *p)
{
	char *input;
	char *tmp;
	int size;

	input = readline("pipe>");
	if(!input)
	{
		printf("Syntax error : Unexpected end of file \n");
		return(0);
	}
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
		if(p->s[*i] == '|')
			return(0);
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
