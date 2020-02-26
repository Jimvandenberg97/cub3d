/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_uitoa.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 17:42:30 by jivan-de       #+#    #+#                */
/*   Updated: 2019/12/07 17:34:40 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char				*ft_uitoa(unsigned int n)
{
	char		*str;
	size_t		i;

	i = ft_getnumlen(n, 10);
	str = (char*)malloc(i + 1);
	if (str == NULL)
		return (NULL);
	str[i] = '\0';
	i--;
	if (n == 0)
		str[0] = '0';
	while (n > 0)
	{
		str[i] = '0' + (n % 10);
		n /= 10;
		i--;
	}
	return (str);
}
