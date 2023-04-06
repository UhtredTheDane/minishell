/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:48:19 by agengemb           #+#    #+#             */
/*   Updated: 2023/04/06 16:44:46 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/signal.h"

int update_signal(int signum, void (*handler)(int))
{
    struct sigaction action;

	ft_bzero(&action, sizeof(action));
	action.sa_handler = handler;
	if (sigaction(signum, &action, NULL) == -1)
    {
        perror("Erreur sigaction\n");
        return (0);
    }
    return (1);
}