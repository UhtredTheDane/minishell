/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:36:00 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/18 01:02:14 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include "../libft/libft.h"
# include <stddef.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include "envp.h"

typedef struct s_envp	t_envp;
typedef struct s_parse	t_parse;

int		update_signal(int signum, void (*handler)(int));
int		update_not_interactive_sigint(int type);
int		update_not_interactive_sigquit(void);
int		init_not_interactive_signals(int type);
int		update_interactive_sigint(void);
int		init_interactive_signals(void);
int		sig_fork(void);
int		sig_main(void);
void	handler_main(int signum);
void	handler_fork(int signum);

#endif
