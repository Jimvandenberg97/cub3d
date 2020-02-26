/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vectors.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/24 16:53:53 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/12 17:53:19 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

/*
** Vector duplicator
*/

void		vector_set(t_vector *dest, t_vector src)
{
	dest->x = src.x;
	dest->y = src.y;
}

/*
** Vector distance calculator
*/

double		vector_distance(t_vector a, t_vector b)
{
	return (sqrt((double)pow(b.x - a.x, 2) + (double)pow(b.y - a.y, 2)));
}

t_vector	vector_new(double x, double y)
{
	t_vector	res;

	res.x = x;
	res.y = y;
	return (res);
}
