#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include "../includes/parsing.h"
# include "envp.h"
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
char	*make_cmd(t_parse *p, char *name_cmd);
char *search_cmd(t_parse *p, t_cmd *cmd, int num_read, int num_write);

int manager(t_parse *p, t_cmd *cmd, int num_proc);
int	run_pipe(t_parse *p);
size_t	count_pipes(char *in_put);

void waiting_all_sons(size_t nb_sons);
void set_num_pipe(t_parse *p, int *num_read, int *num_write, int num_proc);

int	link_stdin(t_parse *p, int num_read);
int	link_stdout(t_parse *p, int num_write);
void	clean_2d_tab(char **tab_2d);
char	*find_path(char **envp, char *cmd, size_t i);
char	*format_string(char *name_cmd);
char	*test_path(char **all_paths, char *cmd_0);
char	*get_path(char *path, char *cmd_0);



void delete_key(t_dico **envp, char *key);

#endif
