/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:24:39 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/07 16:16:00 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/envp.h"

char	**create_envp_tab(t_envp *envp)
{
	char	**tab_envp;
	char	*temp;
	int		nb_env;
	int		i;

	nb_env = ft_envp_size(envp);
	tab_envp = malloc(sizeof(char *) * (nb_env + 1));
	if (!tab_envp)
		return (NULL);
	tab_envp[nb_env] = NULL;
	i = 0;
	while (envp)
	{
		temp = ft_strjoin(envp->key, "=");
		tab_envp[i] = ft_strjoin(temp, envp->value);
		free(temp);
		envp = envp->next;
		++i;
	}
	return (tab_envp);
}

void	delete_dico(t_envp *envp)
{
	t_envp	*elem;
	t_envp	*tempo;

	elem = envp;
	while (elem)
	{
		tempo = elem;
		elem = elem->next;
		free(tempo->key);
		free(tempo->value);
		free(tempo);
	}
}

t_envp	*ft_envp_new(char *key, char *value)
{
	t_envp	*res;

	res = malloc(sizeof(t_envp));
	if (!res)
		return (NULL);
	res->key = key;
	res->value = value;
	res->next = NULL;
	return (res);
}

void	ft_envp_add(t_envp **envp, t_envp *new)
{
	t_envp	*elem;

	if (envp && new)
	{
		if (!*envp)
			*envp = new;
		else
		{
			elem = *envp;
			while (elem->next)
				elem = elem->next;
			elem->next = new;
		}
	}
}
