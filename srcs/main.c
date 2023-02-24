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
		if (in_put)
		{
			add_history(in_put);
			run_pipe(in_put, envp);
			waitpid(-1, &status, 0);

		}
		else
			break;
	}


	return (0);
}
