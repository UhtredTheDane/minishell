/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:09:09 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/24 19:47:26 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"


int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	char	*in_put;
	int	is_alive;
//	int status;
	int pipe_fd[2];

	argc = (int) argc;
	argv = (char **)argv;
	prompt = ">$";
	is_alive = 1;

	while (is_alive)
	{
		in_put = readline(prompt);
		if (in_put)
		{
			add_history(in_put);
			if (pipe(pipe_fd) == -1)
				return (0);	
			run_pipe(pipe_fd, in_put, envp);
			waitpid(-1, NULL, 0);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}
		else
			break;
	}

	return (0);
}
