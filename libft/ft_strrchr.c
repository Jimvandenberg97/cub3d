/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 14:36:30 by jivan-de       #+#    #+#                */
/*   Updated: 2019/11/11 11:49:53 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	*last;

	str = (char*)s;
	last = NULL;
	while (*str != '\0')
	{
		if (*str == c)
			last = str;
		str++;
	}
	if (c == '\0')
		return (str);
	return (last);
}
