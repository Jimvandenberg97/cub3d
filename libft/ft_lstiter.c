/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstiter.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/02 10:25:56 by jivan-de       #+#    #+#                */
/*   Updated: 2019/12/03 14:19:15 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list		*list;

	if (lst == NULL)
		return ;
	list = lst;
	while (list->next != NULL)
	{
		f(list->content);
		list = list->next;
	}
	f(list->content);
}
