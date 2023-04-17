/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:37:09 by lloisel           #+#    #+#             */
/*   Updated: 2023/04/17 14:48:09 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>		 
#include <stdio.h>
#include "../../libft/libft.h"
#include "../../includes/parsing.h"

void	syntax_bis(char *token, t_cmd *cmd)
{
	if (token[0] == '\0' && cmd->next != NULL)
		printf("Syntax error near token : '|'\n");
	else if (token[0] == '\0')
		printf("Syntax error near token : 'newline'\n");
}

void	syntax_err(char *token, t_cmd *cmd)
{
	if (token[0] == '>')
	{
		if (token[1] && token[1] == '>')
			printf("Syntax error near token : '>>'\n");
		else
			printf("Syntax error near token : '>'\n");
	}
	if (token[0] == '<')
	{
		if (token[1] && token[1] == '<')
			printf("Syntax error near token : '<<'\n");
		else
			printf("Syntax error near token : '<'\n");
	}
	syntax_bis(token, cmd);
}

void	error(char *s)
{
	int	l;

	l = ft_strlen(s);
	write(2, s, l);
}
