/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:19:03 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/16 14:21:24 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
  
#ifndef PARSING_H
#define PARSING_H
 # include "envp.h"

typedef struct s_cmd {
	char *s;
	char **cmd;
	struct s_cmd *next;
	void (*f)();
	int in;
	int out;
	char *filename_in;
	char *filename_out;
	int append;
} t_cmd;

typedef struct s_dico t_dico;

typedef struct s_parse {
	char *s;
	int count;
	t_dico *dico;
	int *pipes_fd;
	struct s_cmd *first;	
	struct s_cmd *last;	
} t_parse;

int replace_dollards(t_parse *p,t_dico *envp);
int fill_env(t_cmd *cmd,t_dico *envp, int i);
int is_special(char c,char *charset);
int split_cmd(t_parse *p);
int	execute(t_parse *p);
int add_cmd(t_parse *p ,int start,int end);
t_parse *parsing(char *input, t_dico *envp_dico);
int fill_stdin(t_cmd *cmd,int i);
int fill_stdout(t_cmd *cmd,int i);
void display_parse(t_parse *p);
int free_parse(t_parse *p);
int edit_parsing(t_parse *p);
void display_cmd(t_cmd *cmd);

int skip_to_X(char *s,int i,char *charset);
int skip_space(char *s,int i);
char *trimming(int op,t_cmd *cmd,int start,int end);
#endif
