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

int check_identifier(char *cmd, int egal_pos)
{
	if (!is_entrie_valid(cmd, egal_pos))
	{
		printf("bash: export: '%s': not a valid identifier\n", cmd);
		return (0);
	}
	return (1);
}
int	add_var(t_envp *envp, char *cmd, int egal_pos)
{
	t_envp *new;
	char *key;
    char *value;
	
	cmd[egal_pos] = '\0';
	key = ft_strjoin("", cmd);
    value = ft_strjoin("", cmd + egal_pos + 1);
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

int    builtin_export(t_envp *envp, t_cmd *cmd)
{
	int egal_pos;
	int return_code;
	int i;

	return_code = 0;
	i = 1;
	while (cmd->cmd[i])
	{
        egal_pos = skip_to_X(cmd->cmd[i], 0, "=");
		if (!check_identifier(cmd->cmd[i], egal_pos))
			return_code = 1;
		else
			if (!add_var(envp, cmd->cmd[i], egal_pos))
				return (10);
		++i;
	}
    return (return_code);
}
