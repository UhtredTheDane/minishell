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
	int status;
	int pipe_fd[2];

	if (argc < 1 || argc > 1)
		return (1);
	argv = (char **)argv;
	prompt = ">$";
	while (1)
	{
		in_put = readline(prompt);
		if (in_put)
		{
			add_history(in_put);
			if (pipe(pipe_fd) == -1)
				return (2);	
			if (!run_pipe(pipe_fd, in_put, envp))
			{
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}
			free(in_put);
			waitpid(-1, &status, 0);
		}
		else
			break;
	}
	return (0);
}
