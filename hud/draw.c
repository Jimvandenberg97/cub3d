/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 17:41:33 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/12 17:56:14 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		draw_square(t_config *cfg, t_vector a, t_vector b, int color)
{
	double		y;

	y = a.y;
	while (a.x <= b.x)
	{
		a.y = y;
		while (a.y <= b.y)
		{
			pixel_put(&cfg->images[cfg->img], a.x, a.y, color);
			a.y++;
		}
		a.x++;
	}
}
