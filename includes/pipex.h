#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
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
void manager(char *input_cmd, char **envp, int *pipes_fd, int num_proc, int nb_procs);
void	run_pipe(char **cmds, char **envp, int *pipes_fd, size_t pipes_nb);
int	init_pipe(char *in_put, char **envp);
char	*test_path(char **all_paths, char *cmd_0);
char	*get_path(char *path, char *cmd_0);
char	**make_cmd(char *one_string_cmd, char **envp);
void	clean_2d_tab(char **cmd);
void	clean_exit(char **cmd, int pipe_fd, int file_fd, int exit_value);
char	*format_string(char **cmd);
char	*find_path(char **envp, char **cmd, size_t i);
size_t	count_pipes(char *in_put);
void waiting_all_sons(size_t nb_sons);
size_t	count_pipes(char *in_put);
void close_all_pipes(int *pipes_fd, int nb_pipes);
void	close_useless_pipes(int	*pipes_fd, int num_proc, int nb_procs);

#endif
