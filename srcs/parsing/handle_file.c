/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:42:15 by lloisel           #+#    #+#             */
/*   Updated: 2023/04/18 01:36:41 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"	
#include "../../includes/error.h"	
#include <string.h>
#include <stdio.h>
#include <stdlib.h>		
#include "../../libft/libft.h"

int	handle_bis(t_cmd *cmd)
{
	int	fd;

	unlink(cmd->filename_out);
	fd = open(cmd->filename_out, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
}

int	handle_file(t_cmd *cmd, t_envp *envp)
{
	int		fd;
	char	*tmp;

	tmp = replace_dollards_string(cmd->filename_out, 0, envp);
	cmd->filename_out = trim_quotes(tmp);
	free(tmp);
	fd = open(cmd->filename_out, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		printf("minishell: %s: Is a directory\n", cmd->filename_out);
		return (1);
	}
	if (cmd->append)
	{
		fd = open(cmd->filename_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			return (1);
		close(fd);
	}
	else if (handle_bis(cmd))
		return (1);
	return (0);
}

int	handle_file_stdin(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->filename_in, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		printf("minishell: %s: Is a directory\n", cmd->filename_in);
		return (1);
	}
	fd = open(cmd->filename_in, O_WRONLY, 0644);
	if (fd == -1)
	{
		printf("minishell: %s: no such file \n", cmd->filename_in);
		return (1);
	}
	close(fd);
	return (0);
}
