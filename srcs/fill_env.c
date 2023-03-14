/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 18:48:43 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/14 18:12:30 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/envp.h"
#include "../includes/parsing.h"	
#include <string.h>
#include <stdio.h>
#include <stdlib.h>		
#include "../libft/libft.h"



char *trim_dollard(t_cmd *cmd,int start,int end)
{
	int size;
	char *tmp;
	int i;
	size =end -start;
	 	
	i = 0;
	tmp = malloc(size + 1);
	if(!tmp)
		return(NULL);
	while(i <size)
	{
		tmp[i] = cmd->s[start + i];
		i++;
	}

	tmp[i]='\0';
	printf("tmp : %s \n",tmp);
	return(tmp);
}
int fill_env(t_cmd *cmd,t_dico *envp, int i)
{
	int op;	
	char *value;
	char *tmp;
	op = i;
	i++;
	if(cmd->s[i] && cmd->s[i] == '?')
	{	
		value =getvalue(envp,"?");
		i++;
	}
	else
	{
	
		printf("cmd->s[i] =  |%s|\n",cmd->s + i);
		if(is_special(cmd->s[i]))
			return(1);
		while(cmd->s[i] && !is_special(cmd->s[i]))
			i++;
		printf("cmd->s[i] =  |%s|\n",cmd->s + i);
		value =getvalue(envp, trim_dollard(cmd,op + 1,i));
	}
	printf("value : %s\n",value);
	if(!value)
	{
		printf("VARIABLE DOESNT EXIST\n");
		return(0);
	}	
	cmd->s[op]='\0';	
	tmp = ft_strjoin(cmd->s,value);
	tmp = ft_strjoin(tmp,cmd->s + i);
	cmd->s = tmp;
	free(value);
	display_cmd(cmd);
	return(1);
}
