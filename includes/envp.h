
#ifndef ENVP_H
# define ENVP_H

typedef struct s_dico
{
    char *value;
    char *key;
    struct s_dico *next;

}   t_dico;

t_dico  *create_dico(char **envp);
t_dico	*ft_diconew(char *key, char *value);
char    *getvalue(t_dico *envp, char *key);
int   set_value(t_dico *envp, char *key, char *value);
void	ft_dicoadd(t_dico **lst, t_dico *new);
int	ft_dicosize(t_dico *lst);
char **create_envp_tab(t_dico *dico);

#endif