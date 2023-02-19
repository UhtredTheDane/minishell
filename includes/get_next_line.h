/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 10:43:23 by agengemb          #+#    #+#             */
/*   Updated: 2022/09/30 16:21:41 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	char			content;
	struct s_list	*next;

}			t_list;

char	*get_next_line(int fd);
char	*create_buffer(int fd);
int		is_contains_nl(char *str);
t_list	*ft_lstnew(char content);
void	push_back(t_list **lst, t_list *new);
void	pop_front(t_list **lst);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *list);
t_list	*create_stash(char *buffer, t_list *stash, int octets_read);
char	*create_line(t_list **stash);
#endif
