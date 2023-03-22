/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:09:09 by agengemb          #+#    #+#             */
/*   Updated: 2023/03/10 16:10:18 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include "../includes/main.h"
#include "../includes/envp.h"

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	char	*in_put;
	t_parse *p;
	t_dico *envp_dico;

	if (argc < 1 || argc > 1)
		return (1);
	argv = (char **)argv;
	prompt = ">$";
	envp_dico = create_dico(envp);
	if (!envp_dico)
		return (1);
	if (!init_all_signal())
		return (1);
	while (1)
	{
		in_put = readline(prompt);
		if (in_put)
		{
			p = parsing(in_put, envp_dico);
			if (!p)
			{
				printf("parsing return is NULL\n");
				return (1);
			}
			add_history(in_put);
			if (!execute(p))
				printf("Execution foiree\n");
				
			free(in_put);
		}
		else
			exit(0);
	}
	rl_clear_history();
	return (0);
}
