/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 12:53:06 by lloisel           #+#    #+#             */
/*   Updated: 2023/04/13 14:43:02 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"
#include "../../includes/parsing.h"
#include "../../libft/libft.h"
#include "../../includes/envp.h"
#include <stdio.h>

int	is_empty(char *s)
{
	int	i;

	i = 0;
	while (s[i] && is_special(s[i], " \t"))
		++i;
	if (s[i] == '\0')
		return (1);
	return (0);
}

void	display_cmd(t_cmd *cmd)
{
	int	i;

	printf("  String : %s\n", cmd->s[0]);
	printf("  In : %d\n  Out : %d\n", cmd->in, cmd->out);
	printf("  Filename in : %s \n", cmd->filename_in);
	printf("  Filename out : %s \n", cmd->filename_out);
	printf("  Append : %d\n", cmd->append);
	printf("  Heredocboolean : %d\n", cmd->heredoc);
	i = 0;
	if (cmd->cmd)
	{
		printf("  CMD TAB : \n");
		while (cmd->cmd[i] != NULL)
		{
			printf("  |%s|\n", cmd->cmd[i]);
			++i;
		}
	}
	printf("-------------------\n");
}

void	display_parse(t_parse *p)
{
	t_cmd	*current;
	int		i;

	i = 1;
	current = p->first;
	printf("------ PARSE ------\n");
	printf("  String : %s\n", p->s);
	printf("  Count : %d\n\n", p->count);
	while (current)
	{
		printf("------ CMD %i ------\n", i);
		display_cmd(current);
		current = current->next;
		++i;
	}
	printf("\n");
}

int	skip_space(char *s, int i)
{
	while (s[i] && is_special(s[i], " "))
		i++;
	return (i);
}

int	skip_to_x(char *s, int i, char *charset)
{
	while (s[i] && !is_special(s[i], charset))
		i++;
	return (i);
}
