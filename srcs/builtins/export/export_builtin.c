/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:03:15 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/14 16:40:49 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/builtins.h"

int	is_export(t_cmd *cmd)
{
	size_t	size;

	size = ft_strlen(cmd->cmd[0]);
	if (size < 6)
		size = 6;
	if (ft_strncmp(cmd->cmd[0], "export", size) == 0)
		return (1);
	return (0);
}

int	check_identifier(char *cmd, int egal_pos)
{
	if (egal_pos == 0 || !is_entrie_valid(cmd, egal_pos))
	{
		printf("bash: export: '%s': not a valid identifier\n", cmd);
		return (0);
	}
	return (1);
}

int	add_var(t_envp *envp, char *cmd, int egal_pos)
{
	char	*key;
	char	*value;

	if (cmd[egal_pos] != '\0')
	{
		cmd[egal_pos] = '\0';
		value = new_value(cmd, egal_pos);
		if (!value)
			return (0);
		if (get_value(envp, cmd) != NULL)
			set_value(envp, cmd, value);
		else
		{
			key = new_key(cmd);
			if (!key)
			{
				free(value);
				return (0);
			}
			return (add_new_entries(envp, key, value));
		}
	}
	return (1);
}

int	builtin_export(t_envp *envp, t_cmd *cmd)
{
	int	egal_pos;
	int	return_code;
	int	i;
	char	**char_envp;	
	
	return_code = 0;
	if (!cmd->cmd[1])
	{
		char_envp = create_envp_tab(envp);
		i = 0;
		while (char_envp[i])
		{
			printf("%s\n", char_envp[i]);
			free(char_envp[i]);
			++i;
		}	
	}
	i = 1;
	while (cmd->cmd[i])
	{
		egal_pos = skip_to_x(cmd->cmd[i], 0, "=");
		if (!check_identifier(cmd->cmd[i], egal_pos))
			return_code = 1;
		else
			if (!add_var(envp, cmd->cmd[i], egal_pos))
				return (10);
		++i;
	}
	return (return_code);
}
