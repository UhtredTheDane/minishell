/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:03:30 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/14 16:30:32 by agengemb         ###   ########.fr       */
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

int	check_dollar(t_parse *p)
{
	int	i;
	int	return_code;
	int	dollar_pos;

	i = 0;
	return_code = 0;
	while (dollar_in_str(p->s + i))
	{
		dollar_pos = skip_to_x(p->s, i, "$") + 1;
		i = dollar_pos;
		while (ft_isalnum(p->s[i]))
			++i;
		check_basic_var(p, dollar_pos, i, &return_code);
	}
	return (return_code);
}

int	builtin_unset(t_parse *p, t_cmd *cmd)
{
	char	*key;
	int		i;
	int		return_code;

	return_code = check_dollar(p);
	i = 0;
	while (cmd->cmd[i])
	{
		key = cmd->cmd[i];
		delete_key(&p->envp, key);
		++i;
	}
	return (return_code);
}
