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
			if (!execute(in_put, envp))
			{
				free(in_put);
				return (1);
			}
			free(in_put);
		}
		
	}
	rl_clear_history();
	return (0);
}
