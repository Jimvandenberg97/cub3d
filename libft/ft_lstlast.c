/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 15:19:49 by jivan-de       #+#    #+#                */
/*   Updated: 2019/12/03 14:19:17 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstlast(t_list *lst)
{
	t_list		*list;

	if (lst == NULL)
		return (NULL);
	list = lst;
	while (list->next != NULL)
		list = list->next;
	return (list);
}
