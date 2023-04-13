/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:10:03 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/13 18:27:39 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../includes/envp.h"
# include "../includes/signal.h"
# include "../includes/parsing.h"

typedef struct s_dico	t_dico;
typedef struct s_parse	t_parse;
typedef struct s_envp	t_envp;

int		clean_exit(t_envp *envp);
void	son_proc(char *input_cmd, char **envp, int *pipe_fd, size_t num_proc);
#endif
