/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:19:03 by lloisel           #+#    #+#             */
/*   Updated: 2023/03/06 19:44:23 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_cmd {
	char *:s;
	struct s_cmd *next;
	void (*f)();
} t_cmd;


typedef struct s_parse {
	char *s;
	int count;
	struct s_cmd *first;	
	struct s_cmd *last;	
} t_parse;
