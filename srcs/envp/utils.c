/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 00:48:24 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/13 00:48:26 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/envp.h"

size_t	egal_pos(char *key)
{
	size_t	i;

	i = 0;
	while (key[i])
	{
		if (key[i] == '=')
			return (i);
		++i;
	}
	return (0);
}

size_t	choose_size(char *key, char *elem_key)
{
	size_t	size_key;
	size_t	size_elem_key;

	size_key = ft_strlen(key);
	size_elem_key = ft_strlen(elem_key);
	if (size_key > size_elem_key)
		return (size_key);
	return (size_elem_key);
}

int	ft_envp_size(t_envp *envp)
{
	int	size;

	size = 0;
	while (envp)
	{
		size++;
		envp = envp->next;
	}
	return (size);
}

char	*create_key(char *str, size_t key_len)
{
	char	*key;

	key = malloc(sizeof(char) * (key_len + 1));
	if (!key)
		return (NULL);
	ft_strlcpy(key, str, key_len + 1);
	return (key);
}

char	*create_value(char *str, size_t key_len, size_t value_len)
{
	char	*value;

	value = malloc(sizeof(char) * (value_len + 1));
	if (!value)
		return (NULL);
	ft_strlcpy(value, str + key_len + 1, value_len + 1);
	return (value);
}
