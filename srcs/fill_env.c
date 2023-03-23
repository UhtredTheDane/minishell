/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:48:43 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/23 19:18:42 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/envp.h"
#include "../includes/parsing.h"	
#include <string.h>
#include <stdio.h>
#include <stdlib.h>		
#include "../libft/libft.h"

char *big_join(char *first ,char  *second,char * last)
{
	int size;
	char *new;

	size = ft_strlen(first);
	size =size +ft_strlen(second);
	size = size + ft_strlen(last);
	new  = malloc(sizeof(char)*size +1);
	new[0] = '\0';
	ft_strlcat(new,first,size+1);
	ft_strlcat(new,second,size+1);
	ft_strlcat(new,last,size+1);
	return(new);	
}

char *get_key(t_cmd *cmd ,t_envp *envp,int i,int end)
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
	tmp = get_value(envp,key);
	free(key);
	return(tmp);
}

int change_dollard(t_cmd *cmd,int i, t_envp *envp)
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
	value = get_key(cmd, envp,i + 1,end);
	if(!value)
		return(0);
	cmd->s = big_join(cmd->s,value,cmd->s +end );
	return(1);
}

<<<<<<< HEAD
int replace_dollards_current(t_cmd *current,int i,t_dico *envp)
=======
int replace_dollards(t_parse *p,t_envp *envp)
>>>>>>> origin/alex
{
	while(current->s[++i])
	{
		if(current->s[i] == '$')
		{
			if(!change_dollard(current,i,envp))
				return(0);
		}
		if(current->s[i] == '\'')
			i = skip_to_X(current->s,i+1,"\'");
		if(current->s[i] == '\"')
		{
			while(current->s[++i] && current->s[i] != '\"')
			{
				if(current->s[i] == '$')
				{
					if(!change_dollard(current,i,envp))
						return(0);
				}
			}
		}
	}
	return (1);
}

int replace_dollards(t_parse *p,t_dico *envp)
{
	t_cmd *current;
	int i;

	current = p->first;
	while(current)
	{
		i = -1;
		if(!replace_dollards_current(current,i,envp))
			return (0);
		current = current->next;
	}
	return(1);
}
