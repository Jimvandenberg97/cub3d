/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pixel.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 11:42:25 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/26 17:28:18 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>

/*
** Put pixel with color on the screen at given position
*/

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/*
** [int] - Pixel color of texture at given vector pos
*/

int		get_px(t_texture tex, t_vector pos, int mirror)
{
	if (pos.x < 0)
		pos.x = 0;
	if (pos.y < 0)
		pos.y = 0;
	if (pos.x >= tex.width)
		pos.x = tex.width - 1;
	if (pos.y >= tex.height)
		pos.y = tex.height - 1;
	if (!mirror)
		return (*(int *)(tex.data.addr + (tex.data.line_length * (int)pos.y) +
			(4 * (int)pos.x)));
	else
		return (*(int *)(tex.data.addr + (tex.data.line_length * (int)pos.y) +
			(4 * tex.width) - (((int)pos.x + 1) * 4)));
}

/*
** [int] - Pixel color of position on screen
*/

int		get_screen_px(t_data *data, int x, int y)
{
	return (*(unsigned int *)(data->addr + (y * data->line_length + x *
		(data->bits_per_pixel / 8))));
}
