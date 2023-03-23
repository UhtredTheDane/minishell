
#ifndef ENVP_H
# define ENVP_H

# include "pipex.h"

typedef struct s_envp
{
    char *value;
    char *key;
    struct s_envp *next;

}   t_envp;

t_envp  *create_shell_envp(char **envp);
t_envp	*ft_envp_new(char *key, char *value);
void	ft_envp_add(t_envp**lst, t_envp *new);

int   set_value(t_envp *envp, char *key, char *value);
void delete_key(t_envp **envp, char *key);
char    *get_value(t_envp *envp, char *key);

size_t  egal_pos(char *key);
char **create_envp_tab(t_envp *envp);
int	ft_envp_size(t_envp *envp);

char *create_key(char *str, size_t key_len);
int create_entries(char *str, char **key, char **value);
char *create_value(char *str, size_t key_len, size_t value_len);



#endif
