/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:24:14 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/17 17:16:17 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/envp.h"

int	set_value(t_envp *envp, char *key, char *value)
{
	size_t	size_key;

	while (envp)
	{
		size_key = choose_size(key, envp->key);
		if (ft_strncmp(envp->key, key, size_key) == 0)
		{
			free(envp->value);
			envp->value = value;
			return (1);
		}
		envp = envp->next;
	}
	return (0);
}

void	delete_key(t_envp **envp, char *key)
{
	size_t	size_key;
	t_envp	*prev;
	t_envp	*elem;

	if (envp)
	{
		elem = *envp;
		while (elem)
		{
			size_key = choose_size(key, elem->key);
			if (ft_strncmp(elem->key, key, size_key) == 0)
			{
				free(elem->key);
				free(elem->value);
				if (elem == *envp)
					*envp = elem->next;
				else
					prev->next = elem->next;
				free(elem);
				break ;
			}
			prev = elem;
			elem = elem->next;
		}
	}
}

char	*get_value(t_envp *envp, char *key)
{
	size_t	size_key;

	while (envp)
	{
		size_key = choose_size(key, envp->key);
		if (ft_strncmp(key, envp->key, size_key) == 0)
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}
