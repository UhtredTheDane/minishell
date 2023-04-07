
#ifndef ENVP_H
# define ENVP_H

# include "pipex.h"
  
typedef struct s_envp
{
    char *value;
    char *key;
    struct s_envp *next;

}   t_envp;

void delete_dico(t_envp *envp);
t_envp	*ft_envp_new(char *key, char *value);
void	ft_envp_add(t_envp**lst, t_envp *new);
char **create_envp_tab(t_envp *envp);

int   set_value(t_envp *envp, char *key, char *value);
void delete_key(t_envp **envp, char *key);
char    *get_value(t_envp *envp, char *key);

size_t  egal_pos(char *key);
size_t choose_size(char *key, char *elem_key);
int	ft_envp_size(t_envp *envp);
char *create_key(char *str, size_t key_len);
char *create_value(char *str, size_t key_len, size_t value_len);

int update_shlvl(t_envp *shell_envp);
int add_pwd(t_envp **shell_envp);
int create_entries(char *str, char **key, char **value);
t_envp  *create_shell_envp(char **envp);



#endif
