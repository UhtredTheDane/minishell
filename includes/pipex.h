#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
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
char	**make_cmd(char *one_string_cmd, char **envp);
char **search_cmd(t_config *config, char *input_cmd, int num_read, int num_write);
void manager(t_config *config, char *input_cmd, int num_proc);
void	run_pipe(t_config *config, char **cmds);
int	execute(char *in_put, char **envp);
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
t_dico  *create_dico(char **envp);
t_dico	*ft_diconew(char *key, char *value);
char    *getvalue(t_dico *envp, char *key);
int   set_value(t_dico *envp, char *key, char *value);
void	ft_dicoadd(t_dico **lst, t_dico *new);
int	ft_dicosize(t_dico *lst);
char **create_envp_tab(t_dico *dico);
void    builtin_env(char **envp);
void    builtin_exit(int return_value);
int    builtin_export(t_dico *dico, char *key, char *value);
void    builtin_echo(const char *message, int n_option);
int builtin_cd(t_dico *dico, const char *path);
char *builtin_pwd();

#endif
