/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:40:44 by agengemb          #+#    #+#             */
/*   Updated: 2023/04/13 16:42:25 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include "parsing.h"
# include "execute.h"
# include "envp.h"
# include "builtins.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

extern int	g_rt;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		run_pipe(t_parse *p);
int		link_stdin(t_parse *p, int num_read);
int		link_stdout(t_parse *p, int num_write);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
char	*format_string(char *name_cmd);
pid_t	create_process(t_parse *p);
char	*make_cmd(t_parse *p, char *name_cmd);
char	*search_cmd(t_parse *p, t_cmd *cmd);
size_t	count_pipes(char *in_put);
void	waiting_all_sons(size_t nb_sons, pid_t pid);
void	set_num_pipe(t_parse *p, int *num_read, int *num_write, int num_proc);
void	clean_2d_tab(char **tab_2d);
char	*find_path(char **envp, char *cmd, size_t i);
char	*format_string(char *name_cmd);
char	*test_path(char **all_paths, char *cmd_0);
char	*get_path(char *path, char *cmd_0);
void	close_useless_pipes(t_parse *p, int num_read, int num_write);
void	close_all_pipes(t_parse *p);
#endif
