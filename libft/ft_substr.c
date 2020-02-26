/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 15:50:49 by jivan-de       #+#    #+#                */
/*   Updated: 2019/12/03 14:34:48 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*ptr;
	size_t		i;
	size_t		memlen;

	if (s == NULL)
		return (NULL);
	i = 0;
	memlen = ft_strlen(&s[start]);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (memlen < len)
		len = memlen;
	ptr = malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	while (s[start + i] && i < len)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
