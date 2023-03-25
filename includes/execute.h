#ifndef EXECUTE_H
# define EXECUTE_H

# include "parsing.h"
# include "main.h"

typedef struct s_parse t_parse;
typedef struct s_cmd t_cmd;

int redirect_stdin(t_parse *p, t_cmd *cmd, int num_read);
int redirect_stdout(t_parse *p, t_cmd *cmd, int num_write);
int execute_cmd(t_parse *p, t_cmd *cmd, int old_stdin, int old_stdout);
int manager(t_parse *p, t_cmd *cmd, int num_proc);
int	execute(t_parse *p);

#endif
