
#ifndef ENVP_H
# define ENVP_H

typedef struct s_dico
{
    char *value;
    char *key;
    struct s_dico *next;

}   t_dico;
#endif