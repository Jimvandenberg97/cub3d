/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/02 10:36:57 by jivan-de       #+#    #+#                */
/*   Updated: 2019/12/03 14:40:16 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** HAS TO BE REFACTORED!
*/

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list		*new;
	t_list		*start;

	if (lst == NULL)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	if (new == NULL)
		return (NULL);
	start = new;
	while (lst->next != NULL)
	{
		new->next = ft_lstnew(f(lst->content));
		if (new->next == NULL)
		{
			ft_lstclear(&start, del);
			return (NULL);
		}
		new = new->next;
		lst = lst->next;
	}
	return (start);
}
