/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 12:28:55 by jivan-de       #+#    #+#                */
/*   Updated: 2019/11/09 15:53:26 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	pos;
	size_t	len;

	pos = ft_strlen(dst);
	len = ft_strlen(src);
	if (dstsize == 0)
		return (pos + len);
	if (dstsize < pos)
		len += dstsize;
	else
		len += pos;
	while (src != '\0' && pos + 1 < dstsize)
	{
		dst[pos] = *src;
		pos++;
		src++;
	}
	dst[pos] = '\0';
	return (len);
}
