/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:36:51 by lloisel           #+#    #+#             */
/*   Updated: 2023/04/17 18:18:05 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../libft/libft.h"
#include "../../includes/parsing.h"	
#include "../../includes/main.h"	
#include "../../includes/envp.h"
#include "../../includes/heredoc.h"

void	son_heredoc(t_parse *p, t_cmd *cmd, char *word)
{
	int	return_code;

	return_code = run_heredoc(cmd, word, p->envp);
	free(word);
	exit(return_code);
}

char	*get_key_heredoc(char **tab, t_envp *envp, int i, int end)
{
	char	*key;
	char	*tmp;
	int		index;

	index = 0;
	if (end - i <= 0)
		return (NULL);
	key = malloc(sizeof(char) * (end - i + 1));
	if (!key)
		return (NULL);
	while (i < end)
	{
		key[index] = tab[0][i];
		++i;
		index++;
	}
	key[index] = '\0';
	tmp = get_value(envp, key);
	free(key);
	return (tmp);
}

int	change_dollard_heredoc(char **tmp, int *i, t_envp *envp)
{
	char	*value;
	int		end;

	end = *i + 1;
	if (!tmp[0][end] || is_special(tmp[0][end], "<> \'\""))
	{
		*i = *i + 1;
		return (1);
	}
	else
		tmp[0][*i] = '\0';
	if (tmp[0][end] && tmp[0][end] == '?')
	{
		end++;
		tmp[0] = big_join(tmp[0], ft_itoa(g_rt), tmp[0] + end, 1);
		return (1);
	}
	while (tmp[0][end] && !is_special(tmp[0][end], "<>\" $\'"))
		end++;
	value = get_key_heredoc(tmp, envp, *i + 1, end);
	if (!value)
		tmp[0] = big_join(tmp[0], "", tmp[0] + end, 0);
	else
		tmp[0] = big_join(tmp[0], value, tmp[0] + end, 0);
	return (1);
}

char	*replace_dollards_heredoc(char *input, t_envp *envp)
{
	char	*tmp[1];
	int		i;

	if (!input)
		return (NULL);
	*tmp = input;
	i = 0;
	while (tmp[0][i])
	{
		if (tmp[0][i] == '$')
		{
			if (!change_dollard_heredoc(tmp, &i, envp))
				return (NULL);
		}
		else
			++i;
	}
	return (tmp[0]);
}
