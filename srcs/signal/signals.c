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

#include "../../includes/envp.h"
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

void interactive_signals_handler(int signal)
{
     if(signal == 2)
    {
       	rl_replace_line("", 1);
	    exit(0);
        /*rl_on_new_line();
       	rl_replace_line("", 1);
        rl_redisplay();*/
    }
}






int update_sigint_interactive(int type)
{
	struct sigaction action;
	
    if(type == 0)
    {
        ft_bzero(&action, sizeof(action));
	    action.sa_handler = SIG_IGN;
	    if (sigaction(SIGINT, &action, NULL) == -1)
        {
            perror("Erreur sigaction\n");
            return (0);
        }
        return (1);
    }
    else
    {
	    ft_bzero(&action, sizeof(action));
	    action.sa_handler = SIG_DFL;
	    if (sigaction(SIGINT, &action, NULL) == -1)
        {
            perror("Erreur sigaction\n");
            return (0);
        }
        return (1);
    }
}

void signals_handler(int signal)
{
    if(signal == 2)
    {
        write(0, "\n", 1);
        rl_on_new_line();
       	rl_replace_line("", 1);
        rl_redisplay();
    }
}

int update_sigint_no_interactive(void)
{
	struct sigaction action;
	
	ft_bzero(&action, sizeof(action));
	action.sa_handler = &signals_handler;
	if (sigaction(SIGINT, &action, NULL) == -1)
    {
        perror("Erreur sigaction\n");
        return (0);
    }
    return (1);
}

//Permet d'ignorer sigquit tout au long du minishell
int update_sigquit(void)
{
	struct sigaction action;

	ft_bzero(&action, sizeof(action));
	action.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &action, NULL) == -1)
    {
        perror("Erreur sigaction\n");
        return (0);
    }
    return (1);
}

int update_signal(int signum, void (*sa_handler)(int))
{
    struct sigaction action;

	ft_bzero(&action, sizeof(action));
	action.sa_handler = sa_handler;
	if (sigaction(signum, &action, NULL) == -1)
    {
        perror("Erreur sigaction\n");
        return (0);
    }
    return (1);
}

int init_all_signal_no_interactive()
{
    if (!update_signal(SIGINT, &signals_handler))
        return (0);
    if (!update_signal(SIGQUIT, SIG_IGN))
        return (0);
    return (1);
}
