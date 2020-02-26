/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 13:13:22 by jivan-de       #+#    #+#                */
/*   Updated: 2019/12/03 14:38:07 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list		*ft_lstnew(void *content)
{
	t_list		*list;

	list = (t_list*)malloc(sizeof(*list));
	if (list == NULL)
		return (NULL);
	list->next = NULL;
	list->content = content;
	return (list);
}
