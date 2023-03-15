/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:59:11 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/15 18:03:23 by lloisel          ###   ########.fr       */
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

char *big_join(char *first ,char  *second,char * last)
{
	int size;
	char *new;

	size = ft_strlen(first);
	size =size +ft_strlen(second);
	size = size + ft_strlen(last);
//	printf("Size of new string :%d\n",size);
	new  = malloc(sizeof(char)*size +1);
	new[0] = '\0';
//	printf("First : %s  ",first);
//	printf("Second : %s  ",second);
//	printf("Last : %s  \n",last);
	ft_strlcat(new,first,size+1);
	//printf("new :%s\n",new);
	ft_strlcat(new,second,size+1);
	//printf("new :%s\n",new);
	ft_strlcat(new,last,size+1);
	//free(first);
//	printf("new :%s\n",new);
	return(new);	
}

char *get_key(t_cmd *cmd ,t_dico *envp,int i,int end)
{
	char *key;
	int index;
	char *tmp;
	index = 0;
	if(end - i <= 0)
		return(NULL);
	key = malloc(sizeof(char)*(end-i+1));
	if(!key)
		return(NULL);
	while(i < end)
	{
		key[index] = cmd->s[i];
		i++;
		index++;
	}
	key[index] = '\0';
	tmp = getvalue(envp,key);
	free(key);
	//printf("Key result : %s\n",tmp);
	return(tmp);
}

int change_dollard(t_cmd *cmd,int i, t_dico *envp)
{
	int end;
	char *value;
	
	end = i;
	end++;
	if(is_special(cmd->s[end],"<> \""))
			return(1);
	else
		cmd->s[i] = '\0';
	if(cmd->s[end] && cmd->s[end] == '?')
	{
		printf("$? has been detected , how im i suposed to handle it ?\n");
		return(0);
	}
	while(cmd->s[end] && !is_special(cmd->s[end],"<>\" $"))
		end++;
	value = get_key(cmd,envp,i + 1,end);
	if(!value)
		return(0);
	cmd->s = big_join(cmd->s,value,cmd->s +end );
	//free(value);
	//display_cmd(cmd);	
	return(1);
}

int replace_dollards(t_parse *p,t_dico *envp)
{
	t_cmd *current;
	int i;

	current = p->first;
	while(current)
	{
		i = 0;
		while(current->s[i])
		{
			if(current->s[i] == '$')
			{
				if(!change_dollard(current,i,envp))
							return(0);
			}
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
				{
					if(current->s[i] == '$')
					{
						if(!change_dollard(current,i,envp))
							return(0);
					}
					i++;
				}
			}
			i++;
		}
		current = current->next;
	}
	return(1);
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
		if(!replace_dollards(p,envp_dico))
		{
			printf("we can't replace some variable");
			return(0);

		}	
		display_parse(p);
		if(!edit_parsing(p))
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
