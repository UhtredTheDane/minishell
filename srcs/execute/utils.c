/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:31:04 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/14 23:41:34 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	char_in_str(char c, char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		++i;
	}
	return (0);
}

int	test_acces(t_cmd *cmd)
{
	if (access(cmd->cmd[0], F_OK) == -1)
	{
		printf("minishell: %s: No such file or directory\n", cmd->cmd[0]);
		return (127);
	}
	if (access(cmd->cmd[0], X_OK) == -1)
	{
		printf("minishell: %s: Permission denied\n", cmd->cmd[0]);
		return (126);
	}
	return (0);
}

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

int	already_with_path(t_parse *p, char *cmd)
{
	char	**all_path;
	size_t	i;
	size_t	size;

	if (cmd[0] == '.' && cmd[1] == '/')
		return (1);
	all_path = ft_split(get_value(p->envp, "PATH"), ':');
	if (!all_path)
		return (0);
	i = 0;
	while (all_path[i])
	{
		size = ft_strlen(all_path[i]);
		if (ft_strncmp(all_path[i], cmd, size) == 0)
		{
			clean_2d_tab(all_path);
			return (1);
		}
		++i;
	}
	clean_2d_tab(all_path);
	return (0);
}
