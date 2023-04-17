/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:03:30 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/17 04:07:04 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	is_unset(t_cmd *cmd)
{
	size_t	size;

	size = ft_strlen(cmd->cmd[0]);
	if (size < 5)
		size = 5;
	if (ft_strncmp(cmd->cmd[0], "unset", size) == 0)
		return (1);
	return (0);
}

int	dollar_in_str(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		++i;
	}
	return (0);
}

int	builtin_unset(t_parse *p, t_cmd *cmd)
{
	char	*key;
	int		i;
	int		return_code;
	size_t	size_key;
	char	*error;

	return_code = 0;
	i = 0;
	while (cmd->cmd[i])
	{
		key = cmd->cmd[i];
		size_key = ft_strlen(key);
		if (!size_key || !is_entrie_valid(key, size_key))
		{
			error = ft_strjoin(key, "': not a valid identifier\n");
			write(p->default_out, "unset: '", 8);
			write(p->default_out, error, ft_strlen(error));
			free(error);
			return_code = 1;
		}
		else
			delete_key(&p->envp, key);
		++i;
	}
	return (return_code);
}
