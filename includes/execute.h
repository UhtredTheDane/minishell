#ifndef EXECUTE_H
# define EXECUTE_H

# include "parsing.h"

typedef struct s_parse t_parse;
typedef struct s_cmd t_cmd;

int manager(t_parse *p, t_cmd *cmd, int num_proc);
int	execute(t_parse *p);

#endif
