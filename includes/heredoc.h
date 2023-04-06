#ifndef HEREDOC_H
# define HEREDOC_H

#include "parsing.h"
#include "signal.h"
#include "main.h"
#include "../libft/libft.h"

int max(char *input,char *word);
char *get_name(t_cmd *cmd, int i, int op);
int run_heredoc(t_cmd *cmd, char *word);
int get_heredoc(t_parse *p, t_cmd* cmd, char *word);
int here_doc(t_parse *p, t_cmd *cmd, int i, int op);

#endif
