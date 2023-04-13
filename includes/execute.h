/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:14:56 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/13 17:03:06 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "parsing.h"
# include "main.h"

typedef struct s_parse	t_parse;
typedef struct s_cmd	t_cmd;

extern int			g_rt;

int		run_cmd(t_parse *p, t_cmd *cmd);
int		execute_cmd(t_parse *p, t_cmd *cmd, int old_stdin, int old_stdout);
int		manager(t_parse *p, t_cmd *cmd, int num_proc, int builtin);
int		execute(t_parse *p);
int		char_in_str(char c, char *str);
int		redirect_stdin(t_parse *p, t_cmd *cmd, int num_read);
int		redirect_stdout(t_parse *p, t_cmd *cmd, int num_write);
char	*init_pos_first(int *current_pos, int quote_pos, int double_pos);
char	*rm_first(char *cmd, int *current_pos, int quote_pos, int double_pos);
char	*trim_quotes(char *cmd);
char	**update_for_grep(char **cmd);
char	**add_option_a(char **cmd, int size_cmd);
void	prepare_cmd(t_cmd *cmd);
#endif
