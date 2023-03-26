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

int edit_current(t_cmd *current)
{
	int i;

	i = 0;
	while(current->s[0][i])
	{
		//printf("current edit parsing :%s\n",current->s[0] + i);
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
		else if(current->s[0][i])
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
