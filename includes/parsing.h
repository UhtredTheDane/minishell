/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:19:03 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/14 16:21:35 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/envp.h"
#ifndef PARSING_H
#define PARSING_H


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


typedef struct s_parse {
	char *s;
	int count;
	char **envp;
	struct s_cmd *first;	
	struct s_cmd *last;	
} t_parse;

int fill_env(t_cmd *cmd,t_dico *envp, int i);
int is_special(char c);
int split_cmd(t_parse *p);
int	execute(t_parse *p, char **envp);
int add_cmd(t_parse *p ,int start,int end);
t_parse *parsing(char *input);
int fill_stdin(t_cmd *cmd,int i);
int fill_stdout(t_cmd *cmd,int i,t_dico *envp);
int free_parse(t_parse *p);
int edit_parsing(t_parse *p,t_dico *envp);
void display_cmd(t_cmd *cmd);

#endif
