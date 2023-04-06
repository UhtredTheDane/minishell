/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:45:05 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/27 23:29:17 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "../libft/libft.h"
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include "envp.h"

typedef struct s_envp t_envp;
typedef struct s_parse t_parse;

int clean_exit(t_parse *p,t_envp *envp);
int update_signal(int signum, void (*handler)(int));
int update_sigint_interactive(int type);
void no_interactive_handler(int signal);
int update_no_interactive_sigint();
int init_no_interactive_signals();
#endif
