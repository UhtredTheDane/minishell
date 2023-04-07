/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:10:03 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/06 16:51:46 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
#define MAIN_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "pipex.h"

typedef struct s_dico t_dico;
typedef struct s_parse t_parse;
typedef struct s_envp t_envp;
int clean_exit(t_parse *p,t_envp *envp);
void	son_proc(char *input_cmd, char **envp, int *pipe_fd, size_t num_proc);
#endif
