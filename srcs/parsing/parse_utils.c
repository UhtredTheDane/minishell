/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 12:59:00 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/25 12:59:40 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"
#include "../../includes/parsing.h"
#include "../../libft/libft.h"
#include "../../includes/envp.h"
#include <stdio.h>

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
