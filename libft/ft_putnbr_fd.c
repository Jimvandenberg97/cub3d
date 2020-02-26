/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 12:05:53 by jivan-de       #+#    #+#                */
/*   Updated: 2019/11/02 14:22:47 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		getlen(int num)
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
		num /= 10;
		len++;
	}
	return (len);
}

void				ft_putnbr_fd(int n, int fd)
{
	char	line[11];
	size_t	i;

	i = 0;
	if (n == -2147483648)
		return (ft_putstr_fd("-2147483648", fd));
	i = getlen(n);
	line[i] = '\0';
	i--;
	if (n == 0)
		ft_putchar_fd('0', fd);
	else if (n < 0)
	{
		line[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		line[i] = '0' + (n % 10);
		n /= 10;
		i--;
	}
	ft_putstr_fd(line, fd);
}
