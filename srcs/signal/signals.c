/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:48:19 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/27 22:06:29 by agengemb         ###   ########.fr       */
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

void signals_handler(int signal)
{
    if(signal == 2)
    {
        /*write(0, "\n", 1);
        rl_on_new_line();
       	rl_replace_line("", 1);
        rl_redisplay();*/
    }
}   

void	signal_print_newline(int signal)
{
	(void)signal;
	rl_on_new_line();
}

int update_sigint_interactive(void)
{
	struct sigaction action;
	
	ft_bzero(&action, sizeof(action));
	action.sa_handler = SIG_DFL;
	if (sigaction(SIGINT, &action, NULL) == -1)
    {
        perror("Erreur sigaction\n");
        return (0);
    }
    return (1);
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
