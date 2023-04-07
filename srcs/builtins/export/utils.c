/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:05:18 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/07 16:07:12 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/builtins.h"

int	is_entrie_valid(char *str, int egal_pos)
{
	int	i;

	i = 0;
	while (str[i] && i < egal_pos)
	{
		if (i == 0 && !ft_isalpha(str[i]) && str[i] != '_')
			return (0);
		else
		{
			if (!ft_isalnum(str[i]) && str[i] != '_')
				return (0);
		}
		++i;
	}
	return (1);
}

char	*new_key(char *cmd)
{
	char	*key;

	key = ft_strjoin("", cmd);
	if (!key)
		return (NULL);
	return (key);
}

char	*new_value(char *cmd, int egal_pos)
{
	char	*value;

	value = ft_strjoin("", cmd + egal_pos + 1);
	if (!value)
		return (NULL);
	return (value);
}

int	add_new_entries(t_envp *envp, char *key, char *value)
{
	t_envp	*new;

	new = ft_envp_new(key, value);
	if (!new)
	{
		free(key);
		free(value);
		return (0);
	}
	ft_envp_add(&envp, new);
	return (1);
}
