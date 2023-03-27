/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:48:19 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/27 23:09:56 by agengemb         ###   ########.fr       */
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
        write(0, "\n", 1);
/*	char **tab = malloc(sizeof(char*) * 2);
	tab[0] = ft_strdup("exit");
	tab[1] = NULL;
	execve();*/
	exit(0);
        /*rl_on_new_line();
       	rl_replace_line("", 1);
        rl_redisplay();*/
    }
}

void father_interactive_signals_handler(int signal)
{
     if(signal == 2)
    {
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

void	signal_print_newline(int signal)
{
	(void)signal;
	rl_on_new_line();
}

int update_sigint_interactive(int type)
{
	struct sigaction action;
	
    i f(type == 0)
    {
        ft_bzero(&action, sizeof(action));
	    action.sa_handler = &father_interactive_signals_handlerL;
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

int init_all_signal_no_interactive()
{
    if (!update_sigint_no_interactive())
        return (0);
    if (!update_sigquit())
        return (0);
    return (1);
}
