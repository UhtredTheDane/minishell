/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:09:09 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/19 18:26:04 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	main(int argc, char **argv, char **envp)
{
	char	*prompt;
	char	*in_put;
	int	is_alive;
	char *pwd[2];
	int fd_pwd;

	fd_pwd = open("pwdfichier", O_RDWR | O_CREAT | S_IROTH | S_IWOTH | S_IXOTH);
	if (fd_pwd == -1)
		return (1);
	prompt = "coucou";
	pwd[0] = "/bin/pwd";
	pwd[1] = NULL;	
	is_alive = 1;
	execve(pwd[0], pwd, envp);
	while (is_alive)
	{
		in_put = readline(prompt);
		add_history(in_put);	
	}
	return (0);
}
