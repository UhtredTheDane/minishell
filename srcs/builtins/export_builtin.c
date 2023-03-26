/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:03:15 by agengemb          #+#    #+#             */
/*   Updated: 2023/03/26 03:14:40 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int is_export(t_cmd *cmd)
{
    	if (ft_strncmp(cmd->cmd[0], "export", 6) == 0)
		return (1);
	return (0);
}

int is_entrie_valid(char *str, int egal_pos)
{
	int i;

	i = 0;
	while (str[i] && i < egal_pos)
	{
		if (is
		++i;
	}
}

int is_export(t_parse *p, t_cmd *cmd)
{
	char *key;
	char *value;
	char **entries;
	int egal_pos;
	
	int i;

	i = 1;
	while (cmd->cmd[i])
	{
        	egal_pos = skip_to_X(cmd->cmd[i], 0, "=");
		
		++i;
	}
        key = entries[0];
        value = entries[1];
        free(entries);
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
