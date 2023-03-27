#include "../../includes/signals.h"

int clean_exit()
{

	printf("exit\n");
	return (0); 
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

int  update_sigint_interractive(void)
{
	struct sigaction action;

	ft_bzero(&action, sizeof(action));

	action.sa_handler = &signal_print_newline;
	if (sigaction(SIGINT, &action, NULL) == -1)
	{
		perror("Erreur sigaction\n");
        return (0);
	}
	if (sigaction(SIGQUIT, &action, NULL) == -1)
	{
		perror("Erreur sigaction\n");
        return (0);
	}
	return (1);
}

int update_sigint_interactive(t_parse *p)
{
	struct sigaction action;
	
	
	if (sigaction(SIGINT, p->old_action, NULL) == -1)
    {
        perror("Erreur sigaction\n");
        return (0);
    }
    return (1);
}

int update_sigint(t_parse *p)
{
	struct sigaction action;
	struct sigaction *old_action;
	
	old_action = malloc(sizeof(struct sigaction));
	if (!old_action)
		return (0);
	ft_bzero(&action, sizeof(action));
	ft_bzero(old_action, sizeof(old_action));
	action.sa_handler = &signals_handler;
	if (sigaction(SIGINT, &action, old_action) == -1)
    {
        perror("Erreur sigaction\n");
        return (0);
    }
	p->old_action = old_action;
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

int init_all_signal()
{
    if (!update_sigint())
        return (0);
    if (!update_sigquit())
        return (0);
    return (1);
}
