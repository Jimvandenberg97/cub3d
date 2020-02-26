/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 15:25:30 by jivan-de       #+#    #+#                */
/*   Updated: 2019/11/02 14:19:39 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*a;
	const unsigned char	*b;

	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	a = (unsigned char*)dst;
	b = (const unsigned char*)src;
	while (i < n)
	{
		a[i] = b[i];
		i++;
	}
	return (dst);
}
