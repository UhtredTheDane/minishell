/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollard.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 07:55:22 by lloisel           #+#    #+#             */
/*   Updated: 2023/04/17 14:45:34 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/envp.h"
#include "../../includes/parsing.h"	
#include <string.h>
#include <stdio.h>
#include <stdlib.h>		
#include "../../libft/libft.h"

char	*get_key(char *s, t_envp *envp, int i, int end)
{
	char	*key;
	int		index;
	char	*tmp;

	index = 0;
	if (end - i <= 0)
		return (NULL);
	key = malloc(sizeof(char) * (end - i + 1));
	if (!key)
		return (NULL);
	while (i < end)
	{
		key[index] = s[i];
		i++;
		index++;
	}
	key[index] = '\0';
	tmp = get_value(envp, key);
	free(key);
	return (tmp);
}

int	special_case_dollard(char **s, int end)
{
	if (s[0][end] && is_special(s[0][end], "0123456789?"))
	{
		end++;
		if (s[0][end - 1] == '?')
			s[0] = big_join(s[0], ft_itoa(g_rt), s[0] + end, 1);
		else
			s[0] = big_join(s[0], "", s[0] + end, 0);
		return (1);
	}
	return (0);
}

char	*change_dollard_bis(char *s, int *i, t_envp *envp)
{
	int		end;
	char	*value;

	end = *i + 1;
	if (!s[end] || is_special(s[end], "<> \""))
	{
		*i = *i + 1;
		return (s);
	}
	else
		s[*i] = '\0';
	if (special_case_dollard(&s, end))
		return (s);
	while (s[end] && !is_special(s[end], "=<>\" $\'/"))
		end++;
	value = get_key(s, envp,*i + 1, end);
	if (!value)
		s = big_join(s, "", s + end, 0);
	else
	{
		s = big_join(s, value, s + end, 0);
		*i = *i + ft_strlen(value);
	}
	return (s);
}

char	*change_dollard(char *s, int *i, t_envp *envp)
{
	int		end;
	char	*value;

	end = *i + 1;
	if (!s[end] || is_special(s[end], "<> "))
	{
		*i = *i + 1;
		return (s);
	}
	else
		s[*i] = '\0';
	if (special_case_dollard(&s, end))
		return (s);
	while (s[end] && !is_special(s[end], "=<>\" $\'/"))
		end++;
	value = get_key(s, envp,*i + 1, end);
	if (!value)
		s = big_join(s, "", s + end, 0);
	else
	{
		s = big_join(s, value, s + end, 0);
		*i = *i + ft_strlen(value);
	}
	return (s);
}

char	*replace_dollards_string(char *s, int i, t_envp *envp)
{
	while (s[i])
	{
		if (s[i] == '$')
			s = change_dollard(s, &i, envp);
		if (s[i] == '\'')
			i = skip_to_x(s, i + 1, "\'");
		if (s[i] == '\"')
		{
			while (s[++i] && s[i] != '\"')
			{
				if (s[i] == '$')
				{
					s = change_dollard_bis(s, &i, envp);
					--i;
				}
			}
		}
		if (s[i] && s[i] != '$')
			i++;
	}
	return (s);
}
