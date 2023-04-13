/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 12:54:26 by lloisel           #+#    #+#             */
/*   Updated: 2023/04/13 14:48:18 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"
#include "../../includes/parsing.h"
#include "../../libft/libft.h"
#include "../../includes/envp.h"
#include <stdio.h>

int	to_word_end(char *s, int *i)
{	
	int	size;

	size = *i;
	while (s[*i] && !is_special(s[*i], " "))
	{
		if (s[*i] == '\'')
			*i = skip_to_x(s, *i + 1, "\'") + 1;
		if (s[*i] == '\"')
			*i = skip_to_x(s, *i + 1, "\"") + 1;
		if (s[*i])
			*i = skip_to_x(s, *i, "\"\' ");
	}	
	size = *i - size;
	return (size);
}

int	size_of_tab(char *s)
{
	int	i;
	int	count;

	count = 0;
	i = 0 ;
	i = skip_space(s, i);
	if (!s[i])
		return (0);
	while (s[i] != '\0')
	{
		while (s[i] && !is_special(s[i], " "))
		{
			if (s[i] == '\'')
				i = skip_to_x(s, i + 1, "\'") + 1;
			if (s[i] == '\"')
				i = skip_to_x(s, i + 1, "\"") + 1;
			if (s[i])
				i = skip_to_x(s, i, "\"\' ");
		}
		i = skip_space(s, i);
		count++;
	}
	return (count);
}

int	fill_cell(char *s, int *i, char **tmp)
{
	int	nb;
	int	size_w;

	nb = 0;
	while (s[*i])
	{
		size_w = to_word_end(s, i);
		tmp[nb] = malloc(sizeof(char) * (size_w + 1));
		if (!tmp[nb])
			return (clean_2d_tab(tmp), 0);
		ft_strlcpy(tmp[nb], s + *i - size_w, size_w + 1);
		*i = skip_space(s, *i);
		nb++;
	}
	return (1);
}

char	**create_tab(char *s, int size)
{
	int		i;
	char	**tmp;

	if (!s)
		return (NULL);
	i = 0 ;
	i = skip_space(s, i);
	if (!(*(s + i)))
		return (NULL);
	tmp = malloc(sizeof(char *) * (size + 1));
	if (!tmp)
		return (NULL);
	if (!fill_cell(s, &i, tmp))
		return (NULL);
	tmp[size] = NULL;
	return (tmp);
}

int	split_cmd(t_parse *p)
{
	t_cmd	*current;

	current = p->first;
	while (current)
	{
		current->cmd = create_tab(current->s[0], size_of_tab(current->s[0]));
		current = current->next;
	}
	return (1);
}
