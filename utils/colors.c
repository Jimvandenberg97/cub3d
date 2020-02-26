/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 11:51:40 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/05 16:44:50 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Color resolvers
*/

int		color_argb(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

int		color_a(int color)
{
	return ((color & 0xFF000000) >> 24);
}

int		color_r(int color)
{
	return ((color & 0xFF0000) >> 16);
}

int		color_g(int color)
{
	return ((color & 0xFF00) >> 8);
}

int		color_b(int color)
{
	return (color & 0xFF);
}
