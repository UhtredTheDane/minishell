/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:48:18 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/18 00:55:09 by agengemb         ###   ########.fr       */
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
	else if (signal == 3)
	{
		printf("hello\n");
		write(2, "Quit (core dumped)\n", 19);
		exit(131);
	}
}
