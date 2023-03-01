/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:49:03 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/01 17:13:16 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <string.h>

void action(int signal)
{
	printf("ayayayyaya\n");
	exit(0);
}

void run_signal(void)
{
	struct sigaction action;

	bzero(&action,sizeof(action));
	action.sa_handler = &action;
	sigaction(SIGINT, &action, NULL);
}

int main(void)
{
	run_signal();
	while(1);
	return(0);
}
