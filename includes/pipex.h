#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include "../includes/parsing.h"
# include "config.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
 
# define PROCESSUS_NB 2

char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
char	**make_cmd(char *one_string_cmd, char **envp);
char **search_cmd(t_config *config, char *input_cmd, int num_read, int num_write);
void manager(t_config *config, char *input_cmd, int num_proc);
void	run_pipe(t_config *config, char **cmds);
size_t	count_pipes(char *in_put);
void waiting_all_sons(size_t nb_sons);
void set_num_pipe(t_config *config, int *num_read, int *num_write, int num_proc);
int	link_stdin(t_config *config, int num_read);
int	link_stdout(t_config *config, int num_write);
void	clean_2d_tab(char **tab_2d);
char	*format_string(char **cmd);
char	*find_path(char **envp, char **cmd, size_t i);
char	*test_path(char **all_paths, char *cmd_0);
char	*get_path(char *path, char *cmd_0);

#endif
