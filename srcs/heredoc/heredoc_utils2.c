/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:07:30 by lloisel           #+#    #+#             */
/*   Updated: 2023/04/17 18:33:16 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../libft/libft.h"
#include "../../includes/parsing.h"	
#include "../../includes/main.h"	
#include "../../includes/envp.h"
#include "../../includes/heredoc.h"

int	with_quote(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (is_special(s[i], "\'\""))
			return (1);
		i++;
	}
	return (0);
}

char	*new_delim(t_parse *p, char *s)
{
	char	*tmp;

	tmp = s;
	if (with_quote(tmp))
	{	
		tmp = trim_quotes(s);
		free(s);
		return (tmp);
	}
	else
	{
		tmp = replace_dollards_string(s, 0, p->envp);
		return (tmp);
	}
}
