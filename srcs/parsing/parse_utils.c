/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 12:59:00 by lloisel           #+#    #+#             */
/*   Updated: 2023/04/17 11:46:50 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"
#include "../../includes/parsing.h"
#include "../../libft/libft.h"
#include "../../includes/envp.h"
#include <stdio.h>
#include "../../includes/error.h"

char	*big_join(char *first, char *second, char *last, int c)
{
	int		size;
	char	*new;

	size = ft_strlen(first);
	size = size + ft_strlen(second);
	size = size + ft_strlen(last);
	new = malloc(sizeof(char) * size + 1);
	new[0] = '\0';
	ft_strlcat(new, first, size + 1);
	ft_strlcat(new, second, size + 1);
	ft_strlcat(new, last, size + 1);
	free(first);
	if (c)
		free(second);
	return (new);
}

char	*trimming(int op, t_cmd *cmd, int start, int end)
{
	char	*name;
	char	*tmp;
	int		size;
	int		i;

	i = -1;
	size = end - start;
	if (size <= 0)
		return (NULL);
	name = malloc(sizeof(char) * (size) + 1);
	while (++i < size)
		name[i] = cmd->s[0][start + i];
	name[i] = '\0';
	cmd->s[0][op] = '\0';
	size = (ft_strlen(cmd->s[0]) + ft_strlen(cmd->s[0] + end)) + 1;
	tmp = malloc(size);
	if (!tmp)
		return (NULL);
	tmp[0] = '\0';
	ft_strlcpy(tmp, cmd->s[0], size);
	ft_strlcat(tmp, cmd->s[0] + end, size);
	free(cmd->s[0]);
	cmd->s[0] = tmp;
	return (name);
}

int	is_special(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	single_quote_no_close(char *s, int *i)
{
	*i = *i + 1;
	while (s[*i] != '\0' && s[*i] != '\'')
		*i = *i + 1;
	if (s[*i] == '\0')
		return (error("Syntax error: double quote not close\n"), 1);
	return (0);
}

int	double_quote_no_close(char *s, int *i)
{
	*i = *i + 1;
	while (s[*i] != '\0' && s[*i] != '\"')
		*i = *i + 1;
	if (s[*i] == '\0')
		return (error("Syntax error: double quote not close\n"), 1);
	return (0);
}
