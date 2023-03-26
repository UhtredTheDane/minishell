#include "../../includes/signals.h"

int clean_exit(t_parse *p)
{
	char **cmds;

	cmds = malloc(sizeof(char *) * 2);
	if (!cmds)
	{
		free(p);
		return (1);
	}
	cmds[0] = ft_strjoin("", "exit");
	cmds[1] = NULL;
	p->first->cmd = cmds;
	return (builtin_exit(p->envp, p->first)); 
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

int update_sigint(void)
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

int init_all_signal()
{
    if (!update_sigint())
        return (0);
    if (!update_sigquit())
        return (0);
    return (1);
}
