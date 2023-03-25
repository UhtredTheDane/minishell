/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:10:03 by agengemb          #+#    #+#             */
/*   Updated: 2023/03/25 00:31:55 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
#define MAIN_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "signals.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include "pipex.h"
# include <stdlib.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

typedef struct s_dico t_dico;

void	son_proc(char *input_cmd, char **envp, int *pipe_fd, size_t num_proc);
#endif
