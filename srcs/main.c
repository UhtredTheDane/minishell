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


int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	char	*in_put;
	int	is_alive;
	int status;



	argc = (int) argc;
	argv = (char **)argv;
	prompt = ">$";
	is_alive = 1;
	while (is_alive)
	{
		in_put = readline(prompt);
		add_history(in_put);
		run_pipe(in_put, envp);
		waitpid(-1, &status, 0);
	}


/*
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
	}*/
	return (0);
}
