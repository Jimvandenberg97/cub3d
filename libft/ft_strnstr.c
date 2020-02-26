/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 17:05:34 by jivan-de       #+#    #+#                */
/*   Updated: 2019/11/02 14:50:06 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t			pos;
	size_t			i;

	if (ft_strlen(needle) > ft_strlen(haystack))
		return (NULL);
	if (ft_strlen(needle) == 0 || ft_strlen(haystack) == 0 || len == 0)
		return ((char*)haystack);
	pos = 0;
	while (haystack[pos] != '\0' && pos < len)
	{
		i = 0;
		while (needle[i] != '\0')
			if (pos + i >= len)
				return (NULL);
			else if (haystack[pos + i] == needle[i])
				i++;
			else
				break ;
		if (needle[i] == '\0')
			return ((char*)&haystack[pos]);
		pos++;
	}
	return (NULL);
}
