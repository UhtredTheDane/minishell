/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:09:09 by agengemb          #+#    #+#             */
/*   Updated: 2023/02/19 17:58:19 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	main(char **envp)
{
	char	*prompt;
	char	*in_put;
	int	is_alive;
	char *pwd[2];
	int fd_pwd;

	fd_pwd = open("pwdfichier", O_WRONLY | O_CREAT);
	if (fd_pwd == -1)
		return (1);
	pwd[0] = "/bin/ls";
	pwd[1] = NULL;	
	is_alive = 1;
	if (dup2(fd_pwd, 1) == -1)
		return (2);
	execve(pwd[0], pwd, envp);
	prompt = get_next_line(fd_pwd);
	dup2(STDOUT_FILENO, STDIN_FILENO); 
	while (is_alive)
	{
		in_put = readline(prompt);
		add_history(in_put);	
	}
	return (0);
}
