/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:09:09 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/20 18:33:32 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char	*test_path(char **all_paths, char *cmd_0)
{
	size_t	i;
	char	*good_path;

	i = 0;
	while (all_paths[i])
	{
		good_path = ft_strjoin(all_paths[i], cmd_0);
		if (!good_path)
			return (NULL);
		if (access(good_path, F_OK) == 0)
			return (good_path);
		++i;
		free(good_path);
	}
	return (NULL);
}

char	*get_path(char *path, char *cmd_0)
{
	char	**all_paths;
	char	*cmd_path;

	
	all_paths = ft_split(path, ':');
	if (!all_paths)
		return (NULL);
	cmd_path = test_path(all_paths, cmd_0);
	//clean_2d_tab(all_paths);
	return (cmd_path);
}

char	*find_path(char **envp, char **cmd, size_t i)
{
	char	*temp;

	temp = get_path(envp[i] + 5, cmd[0]);
	if (!temp)
	{
	//	clean_2d_tab(cmd);
		return (NULL);
	}
	free(cmd[0]);
	return (temp);
}

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	char	*in_put;
	int	is_alive;
	char 	**cmd;
	size_t i;
	pid_t	pid;
	int status;

	prompt = ":$";
	is_alive = 1;
	while (is_alive)
	{
		in_put = readline(prompt);
		add_history(in_put);
		cmd = ft_split(in_put, ' ');
		i = 0;
		while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
			++i;
		cmd[0] = ft_strjoin("/", cmd[0]);
		cmd[0] = find_path(envp, cmd, i);
		if (!cmd[0])
			printf("Commande introuvable\n");
		pid = fork();
		if (pid < 0)
		{
			printf("probleme fork\n");
			return (1);
		}
		else if (pid == 0)
		{
			if (execve(cmd[0], cmd, envp) == -1)
				return (1);
		}
		waitpid(-1, &status, 0);
	}
	return (0);
}
