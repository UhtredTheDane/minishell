/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   	interactive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:48:18 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/07 16:50:20 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/signal.h"

void	interactive_handler(int signal)
{
	if (signal == 2)
	{
		write(0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

int	update_interactive_sigint(void)
{
	if (!update_signal(SIGINT, &interactive_handler))
		return (0);
	return (1);
}

//Ignorer SIGQUIT en mode interactif
//En mode non interactif SIGINT reset le prompt
int	init_interactive_signals(void)
{
	if (!update_interactive_sigint())
		return (0);
	if (!update_signal(SIGQUIT, SIG_IGN))
		return (0);
	return (1);
}
