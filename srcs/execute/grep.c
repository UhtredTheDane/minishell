/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grep.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 21:10:00 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/15 21:10:01 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

char	**add_option_a(char **cmd, int size_cmd)
{
	char	**new_cmd;
	int		i;
	int		j;

	new_cmd = malloc(sizeof(char *) * (size_cmd + 2));
	if (!new_cmd)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (j == 1)
			new_cmd[j] = ft_strdup("-a");
		else
			new_cmd[j] = ft_strdup(cmd[i++]);
		if (!new_cmd[j++])
		{
			clean_2d_tab(new_cmd);
			return (NULL);
		}
	}
	new_cmd[j] = NULL;
	return (new_cmd);
}

char	**update_for_grep(char **cmd)
{
	char	**new_cmd;
	int		size_cmd;

	size_cmd = 0;
	while (cmd[size_cmd])
		size_cmd++;
	new_cmd = add_option_a(cmd, size_cmd);
	if (!new_cmd)
		return (cmd);
	clean_2d_tab(cmd);
	return (new_cmd);
}
