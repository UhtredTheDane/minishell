/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:59:11 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/14 16:21:04 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include "../libft/libft.h"
#include "../includes/envp.h"
#include <stdio.h>

int split_cmd(t_parse *p)
{
	t_cmd *current;
	char *tmp;

	current = p->first;	
	while(current)
	{
		tmp = current->s;
		current->cmd = ft_split(current->s, ' ' );
		if(!current->cmd)
			return(0);
		current->s = tmp;
		current= current->next;
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

int edit_parsing(t_parse *p,t_dico *envp)
{
	t_cmd *current;
	int i;
	current = p->first;
	char c;

	while(current)
	{
		i = 0;
		while(current->s[i])
		{
			if(current->s[i] == '\'')		
			{
				printf("SIMPLE QUOTE\n");
				i++;
				while(current->s[i] && current->s[i] != '\'')
					i++;
				printf("After simple quote :%s\n",current->s+i);
			}			
			if(current->s[i] == '\"')
			{
				i++;
				while(current->s[i] && current->s[i] != '\"')
				{
					if(current->s[i] == '$')
					{
						if(!fill_env(current,envp, i))
							return(0);
					}
					else
						i++;
				}
			}
			if(current->s[i] == '$')
			{	
				if(!fill_env(current,envp, i))
					return(0);
			}				
			if(current->s[i] == '<')
			{
				if(!fill_stdin(current,i))
					return(0);
			}
			if(current->s[i] == '>')
			{
				if(!fill_stdout(current,i,envp))
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

int main(int argc,char**argv,char **envp)
{
	t_parse *p;
	t_dico *envp_dico;
	envp_dico = create_dico(envp);
	if(argc  == 2)
	{
		//printf("  INPUT : %s\n",argv[1]);
		p = parsing(argv[1]);
		if(!p)
		{
			printf("arg is not valid for some reasons");	
			return(0);
		}

		p->envp = create_envp_tab(envp_dico); 
		display_parse(p);
		if(!edit_parsing(p,envp_dico))
		{
			printf("parsing has been cancel for some reasons");
			return(0);
		}
		if(!split_cmd(p))
		{
			printf("split failed for some reason");
			return(0);
		}
		else
		{
			display_parse(p);
			free_parse(p);
			return(1);
		}
	}
}
