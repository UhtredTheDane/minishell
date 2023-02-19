/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agengemb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 10:42:45 by agengemb          #+#    #+#             */
/*   Updated: 2022/09/30 16:13:45 by agengemb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_lstnew(char content)
{
	t_list	*res;

	res = malloc(sizeof(t_list));
	if (!res)
		return (NULL);
	res->content = content;
	res->next = NULL;
	return (res);
}

void	push_back(t_list **lst, t_list *new)
{
	t_list	*elem;

	if (lst && new)
	{
		if (*lst == NULL)
			*lst = new;
		else
		{
			elem = *lst;
			while (elem->next != NULL)
				elem = elem->next;
			elem->next = new;
		}
	}
}

void	pop_front(t_list **lst)
{
	t_list	*elem;

	if (lst && *lst)
	{
		elem = *lst;
		*lst = (*lst)->next;
		free(elem);
	}
}

t_list	*ft_lstlast(t_list *lst)
{	
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}
