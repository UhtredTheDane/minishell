/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloisel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:47:53 by lloisel           #+#    #+#             */
/*   Updated: 2023/04/06 16:44:00 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"	
#include "../../includes/main.h"	
#include <string.h>
#include <stdio.h>
#include <stdlib.h>		
#include "../../libft/libft.h"
#include "../../includes/signal.h"

int max(char *input,char *word)
{
	if(ft_strlen(input) > ft_strlen((word)))
		return(ft_strlen(input));
	return (ft_strlen(word));
}

