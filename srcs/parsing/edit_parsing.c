/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:42:42 by lloisel           #+#    #+#             */
/*   Updated: 2023/04/17 15:38:58 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"
#include "../../includes/parsing.h"
#include "../../libft/libft.h"
#include "../../includes/envp.h"
#include <stdio.h>

int	skip_edit(t_cmd *current, int i)
{
	if (current->s[0][i] && current->s[0][i] == '\'')
		i = skip_to_x(current->s[0], i + 1, "\'");
	if (current->s[0][i] && current->s[0][i] == '\"')
		i = skip_to_x(current->s[0], i + 1, "\"");
	return (i);
}

int	edit_current(t_parse *p, t_cmd *current, t_envp *envp)
{
	int	i;
	int	rt;

	i = 0;
	while (current->s[0][i])
	{
		i = skip_edit(current, i);
		if (current->s[0][i] && current->s[0][i] == '<')
		{
			rt = fill_stdin(p, current, i, envp);
			if (rt)
				return (rt);
		}
		else if (current->s[0][i] && current->s[0][i] == '>')
		{
			rt = fill_stdout(current, i, envp);
			if (rt)
				return (rt);
		}
		else if (current->s[0][i])
			i++;
	}
	return (0);
}

int	edit_parsing(t_parse *p, t_envp *envp)
{
	t_cmd	*current;
	int		rt;

	rt = 0;
	current = p->first;
	while (current)
	{
		rt = edit_current(p, current, envp);
		if (rt)
			return (rt);
		current = current->next;
	}
	return (rt);
}
