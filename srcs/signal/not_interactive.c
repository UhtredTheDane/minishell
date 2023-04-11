#include "../../includes/signal.h"

//Type 0 = ignore le signal SIGINT pour le pere pendant le lancement d'un pipe
//Type 1 = reset le comportement par default de SIGINT (utilisé lors d'un pipe pour les fils)
int	update_not_interactive_sigint(int type)
{
	if (type == 0)
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

int update_not_interactive_sigquit(void)
{
	if (!update_signal(SIGQUIT, SIG_DFL))
		return (0);
	return (1);
}

int	init_not_interactive_signals(int type)
{
	if (!update_not_interactive_sigint(type))
		return (0);
	if (!update_not_interactive_sigquit())
		return (0);
	return (1);
}