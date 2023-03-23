/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:24:22 by agengemb          #+#    #+#             */
/*   Updated: 2023/03/23 18:24:23 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/envp.h"

size_t  egal_pos(char *key)
{
    size_t i;

    i = 0;
    while (key[i])
    {
        if (key[i] == '=')
            return (i);
        ++i;
    }
    return (0);
}

char **create_envp_tab(t_envp *envp)
{
    char **tab_envp;
    int nb_env;
    int i;
    char *temp;

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
