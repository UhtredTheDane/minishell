#include "../../includes/signal.h"

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
    if (!update_no_interactive_sigint())
        return (0);
    if (!update_signal(SIGQUIT, SIG_IGN))
        return (0);
    return (1);
}