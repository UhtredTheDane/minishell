/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:24:39 by agengemb          #+#    #+#             */
/*   Updated: 2023/03/23 18:24:41 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/envp.h"

t_envp  *create_shell_envp(char **envp)
{
    size_t  i;
    char *key;
    char *value;
    t_envp *shell_envp;
    size_t keylen;
    size_t valuelen;
    char *lvl;
    int tempo_lvl;
    i = 0;
    shell_envp = NULL;
   
    while (envp[i])
    {
        keylen = egal_pos(envp[i]);
        key = malloc(sizeof(char) * (keylen + 1));
        if (!key)
            return (NULL);
        
        ft_strlcpy(key, envp[i], keylen + 1);
        valuelen = ft_strlen(envp[i] + keylen + 1);
        value = malloc(sizeof(char) * (valuelen + 1));
        if (!value)
            return (NULL);
        ft_strlcpy(value, envp[i] + keylen + 1, valuelen + 1);
        ft_envp_add(&shell_envp, ft_envp_new(key, value));
        ++i;
    }



    lvl = get_value(shell_envp, "SHLVL");
    if (lvl == NULL)
	{
        	lvl = malloc(sizeof(char) * 2);
		if (!lvl)
			return (NULL);
		ft_strlcpy(lvl, "1", 2);
		ft_envp_add(&shell_envp, ft_envp_new("SHLVL", lvl));
    	}
	else
    {
        tempo_lvl = ft_atoi(lvl);
	++tempo_lvl;
	lvl = ft_itoa(tempo_lvl);
	set_value(shell_envp, "SHLVL", lvl);
    }
    return (shell_envp);
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

void	ft_envp_add(t_envp**lst, t_envp *new)
{
	t_envp	*elem;

	if (lst && new)
	{
		if (!*lst)
			*lst = new;
		else
		{
			elem = *lst;
			while (elem->next)
				elem = elem->next;
			elem->next = new;
		}
	}
}
