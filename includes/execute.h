#ifndef EXECUTE_H
# define EXECUTE_H

# include "parsing.h"
# include "main.h"

typedef struct s_parse t_parse;
typedef struct s_cmd t_cmd;
 
char *init_pos_first(int *current_pos, int quote_pos, int double_pos);
char *remove_first(char *cmd, int *current_pos, int quote_pos, int double_pos);
char *trim_quotes(char *cmd);
void prepare_cmd(t_cmd *cmd);
int run_cmd(t_parse *p, t_cmd *cmd);

int execute_cmd(t_parse *p, t_cmd *cmd, int old_stdin, int old_stdout);
int manager(t_parse *p, t_cmd *cmd, int num_proc, int builtin);
int	execute(t_parse *p);

int char_in_str(char c, char *str);
void add_option_a(char **cmd, char **new_cmd);
char **update_for_grep(char **cmd);
int redirect_stdin(t_parse *p, t_cmd *cmd, int num_read);
int redirect_stdout(t_parse *p, t_cmd *cmd, int num_write);

#endif
