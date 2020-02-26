/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_getnumlen.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/07 15:18:33 by jivan-de       #+#    #+#                */
/*   Updated: 2019/12/07 17:00:42 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t		ft_getnumlen(long long num, int base)
{
	size_t		len;

	len = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		num *= -1;
		len++;
	}
	while (num > 0)
	{
		num /= base;
		len++;
	}
	return (len);
}
