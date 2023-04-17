/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:50:50 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/17 22:56:55 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/signal.h"

static void	ms_sig_handler_main(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_rt = 130;
	}
}

static void	ms_sig_handler_fork(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		g_rt = 130;
	}
	else if (signum == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 19);
		g_rt = 131;
	}
}

int	ms_check_sig_fork(void)
{
	if (signal(SIGINT, ms_sig_handler_fork) == SIG_ERR)
	{
		perror("signal");
		return (-1);
	}
	else if (signal(SIGQUIT, ms_sig_handler_fork) == SIG_ERR)
	{
		perror("signal");
		return (-1);
	}
	return (0);
}

int	ms_check_sig_main(void)
{
	if (signal(SIGINT, ms_sig_handler_main) == SIG_ERR)
	{
		perror("signal");
		return (-1);
	}
	else if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("signal");
		return (-1);
	}
	return (0);
}


int	update_signal(int signum, void (*handler)(int))
{
	struct sigaction	action;

	ft_bzero(&action, sizeof(action));
	action.sa_handler = handler;
	if (sigaction(signum, &action, NULL) == -1)
	{
		perror("Erreur sigaction\n");
		return (0);
	}
	return (1);
}
