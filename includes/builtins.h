
#ifndef BULTINS_H
# define BULTINS_H

# define PATH_MAX 4000
# include "pipex.h"
# include "envp.h"
# include "parsing.h"

typedef struct s_cmd t_cmd;
typedef struct s_parse t_parse;
typedef struct s_envp t_envp;

int is_echo(t_cmd *cmd);
int is_pwd(t_cmd *cmd);
int is_cd(t_parse *p, t_cmd *cmd);
int is_unset(t_parse *p, t_cmd *cmd);
int is_export(t_parse *p, t_cmd *cmd);
int is_env(t_parse *p, t_cmd *cmd);
int is_exit(t_parse *p, t_cmd *cmd);
void    builtin_env(char **envp);
void    builtin_exit(t_envp *envp, int return_value);
int    builtin_export(t_envp *envp, char *key, char *value);
void    builtin_echo(char **messages, int n_option);
void builtin_unset(t_envp **envp, char *key);
int builtin_cd(t_envp *envp, const char *path);
char *builtin_pwd();
int is_builtin(t_cmd *cmd);
int execute_builtin(t_parse *p, t_cmd *cmd);
#endif
