/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:36:51 by lloisel           #+#    #+#             */
/*   Updated: 2023/04/07 17:08:03 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include "../../libft/libft.h"
#include "../../includes/parsing.h"	
#include "../../includes/main.h"	
#include "../../includes/envp.h"
#include "../../includes/heredoc.h"

extern int cmd_return;

char *get_key_heredoc(char **tab,t_envp *envp,int i,int end)
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
		key[index] = tab[0][i];
		i++;
		index++;
	}
	key[index] = '\0';
	tmp = get_value(envp,key);
	free(key);
	return(tmp);
}

int change_dollard_heredoc(char **tmp,int *i, t_envp *envp)
{
	int end;
	char *value;
	
	end = *i + 1;
	if(!tmp[0][end] || is_special(tmp[0][end],"<> \'\""))
	{
			*i = *i + 1;
			return(1);
	}
	else
		tmp[0][*i] = '\0';
	if(tmp[0][end] && tmp[0][end] == '?')
	{
		end++;
		tmp[0] = big_join(tmp[0], ft_itoa(cmd_return),tmp[0] +end, 1);
		return(1);
	}
	while(tmp[0][end] && !is_special(tmp[0][end],"<>\" $\'"))
		end++;
	value = get_key_heredoc(tmp, envp,*i + 1,end);
	if(!value)
		tmp[0] = big_join(tmp[0],"",tmp[0] +end ,0);
	else 
		tmp[0] = big_join(tmp[0],value,tmp[0] +end ,0);

	return(1);
}

char *replace_dollards_heredoc(char *input,t_envp *envp)
{
	int i;
	char *tmp[1];

	if(!input)
		return(NULL);
	*tmp = input;	
	i = 0;
	while(tmp[0][i])
	{
		if(tmp[0][i] =='$')
		{
			if(!change_dollard_heredoc(tmp,&i,envp))
				return(NULL);
		}
		else
			i++;
	}
	return (tmp[0]);
}
