/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:03:30 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/17 00:46:54 by agengemb         ###   ########.fr       */
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

void	check_basic_var(t_parse *p, int dollar_pos, int i, int *return_code)
{
	char	*name_var;
	char	*value_var;
	char	*tempo_value;
	int		size_name;

	size_name = i - dollar_pos;
	name_var = malloc(sizeof(char) * (size_name + 1));
	if (name_var)
	{
		ft_strlcpy(name_var, p->s + dollar_pos, size_name + 1);
		value_var = getenv(name_var);
		if (value_var)
		{
			tempo_value = get_value(p->envp, name_var);
			if (tempo_value)
				printf("bash: unset: '%s': not a valid identifier\n",
						tempo_value);
			*return_code = 1;
		}
		free(name_var);
	}
}


int	builtin_unset(t_parse *p, t_cmd *cmd)
{
	char	*key;
	int		i;
	int		return_code;
	size_t	size_key;

	return_code = 0;
	i = 0;
	while (cmd->cmd[i])
	{
		key = cmd->cmd[i];
		size_key = ft_strlen(key);
		if (!size_key || !is_entrie_valid(key, size_key))
		{
			printf("bash: unset: '%s': not a valid identifier\n", key);
			return_code = 1;
		}
		else
			delete_key(&p->envp, key);
		++i;
	}
	return (return_code);
}
