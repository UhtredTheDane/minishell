/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:58:02 by lloisel           #+#    #+#             */
/*   Updated: 2023/04/17 14:43:42 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "envp.h"
# include "signal.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>

typedef struct s_cmd {
	struct s_cmd	*next;
	char			**s;
	char			**cmd;
	char			*filename_in;
	char			*filename_out;
	int				in;
	int				out;
	int				append;
	int				heredoc;
	int				*pipe_heredoc;
}			t_cmd;

typedef struct s_envp	t_envp;

typedef struct s_parse {
	struct s_cmd	*first;
	struct s_cmd	*last;
	t_envp			*envp;
	char			*s;
	int				count;
	int				*pipes_fd;	
}			t_parse;

extern int				g_rt;


char	*get_key(char *s, t_envp *envp, int i, int end);
int	handle_file(t_cmd *cmd, t_envp *envp);
char *replace_dollards_string(char *s, int i, t_envp *envp);
char	*get_name(t_cmd *cmd, int i, int op);
char	*big_join(char *first, char *second, char *last, int c);
char	*trimming(int op, t_cmd *cmd, int start, int end);
int		replace_dollards(t_parse *p, t_envp *envp);
int		fill_env(t_cmd *cmd, t_envp *envp, int i);
int		is_special(char c, char *charset);
int		split_cmd(t_parse *p);
int		execute(t_parse *p, t_envp *envp);
int		add_cmd(t_parse *p, int start, int end);
int		is_empty(char *s);
int		here_doc(t_parse *p, t_cmd *cmd, int i, int op);
int		double_quote_no_close(char *s, int *i);
int		single_quote_no_close(char *s, int *i);
int		add_cmd(t_parse *p, int start, int end);
int		fill_stdin(t_parse *p, t_cmd *cmd, int i, t_envp *envp);
int		fill_stdout(t_cmd *cmd, int i, t_envp *envp);
int		edit_parsing(t_parse *p, t_envp *envp);
int		skip_to_x(char *s, int i, char *charset);
int		skip_space(char *s, int i);
t_parse	*init_parse(t_envp *envp_dico);
t_parse *parsing(char *input, t_envp *envp_dico, int *rt);
void	display_parse(t_parse *p);
void	free_parse(t_parse *p);
void	display_cmd(t_cmd *cmd);
#endif
