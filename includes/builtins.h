
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
int is_unset(t_parse *p, t_cmd *cmd);
int is_export(t_parse *p, t_cmd *cmd);
int is_env(t_parse *p, t_cmd *cmd);
int is_exit(t_parse *p, t_cmd *cmd);

void    builtin_env(char **envp);

void    builtin_exit(t_envp *envp, int return_value);

int    builtin_export(t_envp *envp, char *key, char *value);

void    builtin_echo(char **messages, int n_option);

void builtin_unset(t_envp **envp, char *key);

int is_builtin(t_cmd *cmd);

int is_cd(t_cmd *cmd);
int builtin_cd(t_envp *envp, t_cmd *cmd);
int update_env(t_envp *envp);
int env_with_pwd(t_envp *envp, char *pwd, char **new_pwd, char **old_pwd);
char  *env_with_no_pwd();
int check_path(const char *path);
char *init_path(t_cmd *cmd);




char *builtin_pwd();

int is_builtin(t_cmd *cmd);
int execute_builtin(t_parse *p, t_cmd *cmd);
#endif
