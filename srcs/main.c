/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:09:09 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/20 15:57:00 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	char	*in_put;
	int	is_alive;

	prompt = ":$";
	is_alive = 1;
	while (is_alive)
	{
		in_put = readline(prompt);
		add_history(in_put);	
		
	}
	return (0);
}
