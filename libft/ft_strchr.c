/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 14:36:30 by jivan-de       #+#    #+#                */
/*   Updated: 2019/10/29 15:42:02 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char*)s;
	while (*str != '\0')
		if (*str == c)
			return (str);
		else
			str++;
	if (c == '\0')
		return (str);
	return (NULL);
}
