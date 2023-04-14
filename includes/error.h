/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:38:33 by lloisel           #+#    #+#             */
/*   Updated: 2023/04/14 17:39:05 by lloisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdlib.h>		 
# include <stdio.h>
# include "parsing.h"

void	syntax_err(char *token,t_cmd *cmd);
void	error(char *s);

#endif

