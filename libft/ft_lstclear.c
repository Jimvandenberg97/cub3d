/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 19:00:57 by jivan-de       #+#    #+#                */
/*   Updated: 2019/12/03 14:38:23 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list		*list;
	t_list		*new;

	if (lst == NULL || *lst == NULL)
		return ;
	list = *lst;
	while (list != NULL)
	{
		new = list;
		list = list->next;
		del(new->content);
		free(new);
	}
	*lst = NULL;
}
