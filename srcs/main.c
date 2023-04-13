/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:09:09 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/13 18:26:42 by agengemb         ###   ########.fr       */
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

void	cmd_treatment(t_envp *envp_dico, char *in_put)
{
	t_parse	*p;

	p = parsing(in_put, envp_dico);
	if (p)
	{
		add_history(p->s);
		if (!replace_dollards(p, envp_dico))
			printf("we can't replace some variable");
		else
			execute(p);
		free_parse(p);
	}
	free(in_put);
}

int	main_loop(t_envp *envp_dico, char *prompt)
{
	char	*in_put;

	while (1)
	{
		in_put = readline(prompt);
		if (in_put)
			cmd_treatment(envp_dico, in_put);
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
