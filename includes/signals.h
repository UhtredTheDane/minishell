#ifndef SIGNALS_H
# define SIGNALS_H

# include "../libft/libft.h"
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include "parsing.h"

typedef struct s_parse t_parse;

int clean_exit();
void signals_handler(int signal);
int update_sigint(void);

int init_all_signal();
#endif
