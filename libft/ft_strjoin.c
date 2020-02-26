/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 16:14:41 by jivan-de       #+#    #+#                */
/*   Updated: 2020/01/16 13:04:20 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		l1;
	int		l2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	str = (char *)malloc(l1 + l2 + 1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, l1 + 1);
	ft_strlcat(str, s2, l1 + l2 + 1);
	return (str);
}

char		*ft_strjoin_free1(char const *s1, char const *s2)
{
	char	*str;
	int		l1;
	int		l2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	str = (char *)malloc(l1 + l2 + 1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, l1 + 1);
	ft_strlcat(str, s2, l1 + l2 + 1);
	free((char *)s1);
	return (str);
}

char		*ft_strjoin_free2(char const *s1, char const *s2)
{
	char	*str;
	int		l1;
	int		l2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	str = (char *)malloc(l1 + l2 + 1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, l1 + 1);
	ft_strlcat(str, s2, l1 + l2 + 1);
	free((char *)s2);
	return (str);
}

char		*ft_strjoin_free12(char const *s1, char const *s2)
{
	char	*str;
	int		l1;
	int		l2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	str = (char *)malloc(l1 + l2 + 1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, l1 + 1);
	ft_strlcat(str, s2, l1 + l2 + 1);
	free((char *)s1);
	free((char *)s2);
	return (str);
}
