#ifndef BULTINS_H
#define BULTINS_H
# include "envp.h"

void    builtin_env(char **envp);
void    builtin_exit(int return_value);
int    builtin_export(t_dico *dico, char *key, char *value);
void    builtin_echo(const char *message, int n_option);
void builtin_unset(t_dico **dico, char *key);
int builtin_cd(t_dico *dico, const char *path);
char *builtin_pwd();
int is_builtin(t_parse *p, t_cmd *cmd);
#endif