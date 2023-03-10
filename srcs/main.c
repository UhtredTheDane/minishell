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
	t_dico *envp_dico;
	char **mini_envp;

	if (argc < 1 || argc > 1)
		return (1);
	argv = (char **)argv;
	prompt = ">$";
	envp_dico = create_dico(envp);
	if (!envp_dico)
		return (1);
	if (!init_all_signal())
		return (1);
	mini_envp = create_envp_tab(envp_dico);
	while (1)
	{
		in_put = readline(prompt);
		if (in_put)
		{
			add_history(in_put);
			if (ft_strncmp(in_put, "env", 3) == 0)
				builtin_env(mini_envp);
			else if (ft_strncmp(in_put, "exit", 4) == 0)
				builtin_exit(1);
			else if (!execute(in_put, mini_envp))
			{
				free(in_put);
				return (1);
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
