/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:19:03 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/10 18:01:57 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MAIN_H
#define MAIN_H


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
	struct s_cmd *first;	
	struct s_cmd *last;	
} t_parse;

int	execute(t_parse *p, char **envp);
int add_cmd(t_parse *p ,int start,int end);
t_parse *parsing(char *input);
int fill_stdin(t_cmd *cmd,int i);
int fill_stdout(t_cmd *cmd,int i);
int free_parse(t_parse *p);
#endif
