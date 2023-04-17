/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:50:50 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/18 00:59:31 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/signal.h"

void	handler_main(int signum)
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

int	update_interactive_sigint(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		return (0);
	return (1);
}

void	handler_fork(int signum)
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

int	sig_fork(void)
{
	if (signal(SIGINT, handler_fork) == SIG_ERR)
		return (-1);
	else if (signal(SIGQUIT, handler_fork) == SIG_ERR)
		return (-1);
	return (0);
}

int	sig_main(void)
{
	if (signal(SIGINT, handler_main) == SIG_ERR)
		return (-1);
	else if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (-1);
	return (0);
}
