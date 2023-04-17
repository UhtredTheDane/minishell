/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:09:09 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/17 18:51:26 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	g_rt = 0;

int	clean_exit(t_envp *envp)
{	
	delete_dico(envp);
	rl_clear_history();
	printf("exit\n");
	return (0);
}

int	cmd_treatment(t_envp *envp_dico, char *in_put)
{
	t_parse	*p;
	int		rt;

	rt = 0;
	if (is_empty(in_put))
		return (free(in_put), 0);
	p = parsing(in_put, envp_dico, &rt);
	if (!rt && p)
	{
		rt = execute(p, envp_dico);
		if (rt)
			return (free_parse(p), free(in_put), rt);
		free_parse(p);
	}
	free(in_put);
	return (rt);
}

int	main_loop(t_envp *envp_dico, char *prompt)
{
	char	*in_put;
	int rt;

	
	while (1)
	{
		in_put = readline(prompt);
		if (in_put)
		{
			rt = cmd_treatment(envp_dico, in_put);
			if(rt)
				g_rt = rt;		
		}
		else
			return (clean_exit(envp_dico));
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	t_envp	*envp_dico;

	if (argc < 1 || argc > 1)
		return (1);
	argv = (char **)argv;
	prompt = "Minishell :";
	envp_dico = create_shell_envp(envp);
	if (!envp_dico || !init_interactive_signals())
		return (1);
	return (main_loop(envp_dico, prompt));
}
