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
	char **mini_envp;

	if (argc < 1 || argc > 1)
		return (1);
	argv = (char **)argv;
	prompt = ">$";
	envp_dico = create_dico(envp);
	if (!envp_dico)
		return (1);
	builtin_unset(&envp_dico, "SYSTEMD_EXEC_PID");
	if (!init_all_signal())
		return (1);
	mini_envp = create_envp_tab(envp_dico);
	while (1)
	{
		in_put = readline(prompt);
		if (in_put)
		{
			p = parsing(input);
			if(!p)
				printf("parsing return is NULL\n");
			else

			add_history(in_put);
			if (ft_strncmp(in_put, "env", 3) == 0)
				builtin_env(mini_envp);
			else if (ft_strncmp(in_put, "exit", 4) == 0)
				builtin_exit(1);
			else if (!execute(in_put, mini_envp))

			{
				add_history(in_put);
				if (!execute(p, envp))
					return (free(in_put),1);
				free(in_put);
			}
			free(in_put);
			mini_envp = create_envp_tab(envp_dico);
		}
		else
			exit(0);
	}
	rl_clear_history();
	return (0);
}
