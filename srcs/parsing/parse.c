/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:17:21 by lloisel           #+#    #+#             */
/*   Updated: 2023/04/17 14:31:10 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../includes/parsing.h"
#include "../../includes/error.h"
#include <unistd.h>
#include "../../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

int	pipe_at_end(t_parse *p)
{
	char	*input;
	char	*tmp;
	int		size;

	input = readline("pipe>");
	if (!input)
	{
		printf("Syntax error : Unexpected end of file \n");
		return (2);
	}
	size = ft_strlen(input) + ft_strlen(p->s) + 1;
	tmp = malloc(sizeof(char) * size);
	if (!tmp)
		return (2);
	tmp[0] = '\0';
	ft_strlcat(tmp, p->s, size);
	ft_strlcat(tmp, input, size);
	free(input);
	free(p->s);
	p->s = tmp;
	return (0);
}

int	parse_bis(t_parse *p, int *i, int *start_w)
{
	int	rt;

	rt = 0;
	if (p->s[*i] && p->s[*i] == '|')
	{
		rt = add_cmd(p, *start_w, *i);
		if (rt)
			return (rt);
		*start_w = *i + 1;
		*i = skip_space(p->s, *i + 1);
		if (p->s[*i] == '|')
			return (error("Syntax error Unexpected token : '|'\n"), 2);
		if (p->s[*i] == '\0')
		{
			if (pipe_at_end(p) == 2)
				return (2);
		}
	}
	if (p->s[*i] == '\'' && single_quote_no_close(p->s, i))
		return (1);
	if (p->s[*i] == '\"' && double_quote_no_close(p->s, i))
		return (1);
	return (0);
}

int	parse(char *input, t_parse *p)
{
	int	i;
	int	start_w;

	i = -1;
	start_w = 0;
	p->s = malloc(sizeof(char ) * ft_strlen(input) + 1);
	if (!p->s)
		return (1);
	p->s[0] = '\0';
	ft_strlcat(p->s, input, ft_strlen(input) + 1);
	while (p->s[++i] && p->s[i] != '\0')
	{
		if (parse_bis(p, &i, &start_w))
		{
			add_history(p->s);
			return (2);
		}
	}
	add_history(p->s);
	i = add_cmd(p, start_w, i);
	if (i)
		return (i);
	return (0);
}

int	pipe_parse(t_parse *p)
{
	int	i;

	i = 0;
	while (i < (p->count - 1) * 2)
	{
		if (pipe(p->pipes_fd + i) == -1)
			return (1);
		i += 2;
	}
	return (0);
}

t_parse	*parsing(char *input, t_envp *envp_dico, int *rt)
{
	t_parse	*p;

	*rt = 0;
	p = init_parse(envp_dico);
	if (!p)
		return (NULL);
	*rt = parse(input, p);
	if (*rt)
		return (free_parse(p), NULL);
	if (p->count < 2)
		p->pipes_fd = NULL;
	else
	{
		p->pipes_fd = malloc(sizeof(int) * (p->count - 1) * 2);
		if (!p->pipes_fd)
		{
			*rt = 1;
			return (free_parse(p), NULL);
		}
	}
	*rt = pipe_parse(p);
	if (*rt)
		return (free_parse(p), NULL);
	return (p);
}
