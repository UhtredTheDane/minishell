/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:42:46 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/13 16:44:35 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "parsing.h"
# include "signal.h"
# include "main.h"
# include "../libft/libft.h"

extern int	g_rt;

int		max(char *input, char *word);
int		run_heredoc(t_cmd *cmd, char *word, t_envp *envp);
int		get_heredoc(t_parse *p, t_cmd *cmd, char *word);
int		here_doc(t_parse *p, t_cmd *cmd, int i, int op);
void	son_heredoc(t_parse *p, t_cmd *cmd, char *word);
char	*replace_dollards_heredoc(char *input, t_envp *envp);
char	*get_name(t_cmd *cmd, int i, int op);
#endif
