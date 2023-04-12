/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_interactive.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 00:42:17 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/13 00:43:42 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/signal.h"

//Type 0 = ignore SIGINT pour le pere pendant le lancement d'un pipe
//Type 1 = reset SIGINT par default(lors d'un pipe pour les fils)
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

int	update_not_interactive_sigquit(void)
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
