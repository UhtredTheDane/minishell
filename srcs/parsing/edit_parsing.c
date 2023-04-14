/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:42:42 by lloisel           #+#    #+#             */
/*   Updated: 2023/04/14 20:35:56 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"
#include "../../includes/parsing.h"
#include "../../libft/libft.h"
#include "../../includes/envp.h"
#include <stdio.h>

int	edit_current(t_parse *p, t_cmd *current)
{
	int	i;

	i = 0;
	while (current->s[0][i])
	{
		if (current->s[0][i] && current->s[0][i] == '\'')
			i = skip_to_x(current->s[0], i + 1, "\'");
		if (current->s[0][i] && current->s[0][i] == '\"')
			i = skip_to_x(current->s[0], i + 1, "\"");
		if (current->s[0][i] && current->s[0][i] == '<')
		{
			if (!fill_stdin(p, current, i))
				return (0);
		}
		else if (current->s[0][i] && current->s[0][i] == '>')
		{
			if (!fill_stdout(current, i))
				return (0);
		}
		else if (current->s[0][i])
			i++;
	}
	return (1);
}

int	edit_parsing(t_parse *p)
{
	t_cmd	*current;

	current = p->first;
	while (current)
	{
		if (!edit_current(p, current))
			return (0);
		current = current->next;
	}
	return (1);
}
