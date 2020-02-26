/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 17:10:48 by jivan-de       #+#    #+#                */
/*   Updated: 2019/11/04 13:54:01 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*a;
	const unsigned char	*b;

	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	a = (unsigned char*)dst;
	b = (const unsigned char*)src;
	if (b < a)
	{
		i++;
		while (i <= len)
		{
			a[len - i] = b[len - i];
			i++;
		}
	}
	else
		ft_memcpy(a, b, len);
	return (dst);
}
