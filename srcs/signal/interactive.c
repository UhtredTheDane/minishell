/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:45:54 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/07 16:48:08 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/signal.h"

//Type 0 = ignore le signal SIGINT pour le pere pendant le lancement d'un pipe
//Type 1 = reset le comportement par default de SIGINT (utilisé lors d'un pipe pour les fils)

int	update_sigint_interactive(int type)
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
