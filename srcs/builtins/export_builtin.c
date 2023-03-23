/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:03:15 by agengemb          #+#    #+#             */
/*   Updated: 2023/03/23 18:15:00 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int is_export(t_parse *p, t_cmd *cmd)
{
    char *key;
    char *value;
    char **entries;

    if (ft_strncmp(cmd->cmd[0], "export", 6) == 0)
    {
        entries = ft_split(cmd->cmd[1], '=');
        if (!entries)
            return (0);
        key = entries[0];
        value = entries[1];
        builtin_export(p->envp, key, value);
        free(entries);
        return (1);
    }
    return (0);
}

int    builtin_export(t_envp *envp, char *key, char *value)
{
    t_envp *new;

    new = ft_envp_new(key, value);
    if (!new)
        return (0);
    ft_envp_add(&envp, new);
    return (1);
}
