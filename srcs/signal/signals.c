/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:48:19 by agengemb           #+#    #+#             */
/*   Updated: 2023/03/28 00:31:56 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/signals.h"

int clean_exit(t_parse *p,t_envp *envp)
{
	if(p)
		free_parse(p);	
	delete_dico(envp);
	rl_clear_history();	
	printf("exit\n");
	return (0); 
}

int update_signal(int signum, void (*handler)(int))
{
    struct sigaction action;

	ft_bzero(&action, sizeof(action));
	action.sa_handler = handler;
	if (sigaction(signum, &action, NULL) == -1)
    {
        perror("Erreur sigaction\n");
        return (0);
    }
    return (1);
}

//Type 0 = ignore le signal SIGINT pour le pere pendant le lancement d'un pipe
//Type 1 = reset le comportement par default de SIGINT (utilisé lors d'un pipe pour les fils)

int update_sigint_interactive(int type)
{
    if(type == 0)
    {
        if (!update_signal(SIGINT, SIG_IGN))
            return (0);
    }
    else
    {
        if (!update_signal(SIGINT, SIG_DFL))
            return (0);
    }
    return (1);
}

void no_interactive_handler(int signal)
{
    if(signal == 2)
    {
        write(0, "\n", 1);
        rl_on_new_line();
       	rl_replace_line("", 1);
        rl_redisplay();
    }
}

int update_no_interactive_sigint()
{
	if (!update_signal(SIGINT, &no_interactive_handler))
        return (0);
    return (1);
}

//Ignorer SIGQUIT en mode interactif ou non
//Faire qu'en mode non interactif SIGINT reset le prompt
int init_no_interactive_signals()
{
    if (!update_sigint_interactive())
        return (0);
    if (!update_signal(SIGQUIT, SIG_IGN))
        return (0);
    return (1);
}
