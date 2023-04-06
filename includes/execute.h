#ifndef EXECUTE_H
# define EXECUTE_H

# include "parsing.h"
# include "main.h"

typedef struct s_parse t_parse;
typedef struct s_cmd t_cmd;

char **update_for_grep(char **cmd);
char *remove_first(char *cmd, int *current_pos, int quote_pos, int double_pos);
char *trim_quotes(char *cmd);
void prepare_cmd(t_cmd *cmd);
int execute_cmd(t_parse *p, t_cmd *cmd, int old_stdin, int old_stdout);

int manager(t_parse *p, t_cmd *cmd, int num_proc);
int	execute(t_parse *p);

int char_in_str(char c, char *str);
int redirect_stdin(t_parse *p, t_cmd *cmd, int num_read);
int redirect_stdout(t_parse *p, t_cmd *cmd, int num_write);

#endif
