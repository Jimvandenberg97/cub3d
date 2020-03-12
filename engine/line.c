/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   line.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 11:48:53 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/28 18:10:31 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

/*
** Calculate wall pixel color and positions
*/

static void		render_walls(t_config *cfg, int *i, int tex, int x)
{
	double		wallx;
	t_vector	texture;
	int			color;

	if (cfg->player.side == 0)
		wallx = cfg->player.pos.y + cfg->player.pwalldist * cfg->player.ray.y;
	else
		wallx = cfg->player.pos.x + cfg->player.pwalldist * cfg->player.ray.x;
	wallx -= floor((wallx));
	texture.x = (int)(wallx * cfg->textures[tex].width);
	while (*i <= cfg->player.lineend && *i < cfg->height)
	{
		texture.y = (int)(((*i - cfg->height * .5 + cfg->player.lineheight * .5)
				* cfg->textures[tex].height) / cfg->player.lineheight);
		if (texture.y >= cfg->textures[tex].height)
			texture.y--;
		texture.y = texture.y < 0 ? 0 : texture.y;
		color = get_px(cfg->textures[tex], texture,
			(cfg->player.side == 1) ? 1 : 0);
		if (cfg->player.side == 1)
			color = (color >> 1) & 8355711;
		if (in_square(cfg->port_start, cfg->port_end, vector_new(x, *i)))
			pixel_put(&cfg->images[cfg->img], x, *i, color);
		(*i)++;
	}
}

/*
** Draw vertical line across screen
*/

void			line_put(int x, t_config *cfg, int tex)
{
	int		i;

	i = 0;
	if (!cfg->options[OPT_CEILTEXT])
		while (i < cfg->player.linestart)
		{
			if (in_square(cfg->port_start, cfg->port_end, vector_new(x, i)))
				pixel_put(&cfg->images[cfg->img], x, i, cfg->color_ceil);
			i++;
		}
	else
		i = cfg->player.linestart;
	render_walls(cfg, &i, tex, x);
	if (!cfg->options[OPT_FLOORTEXT])
		while (i < cfg->height)
		{
			if (in_square(cfg->port_start, cfg->port_end, vector_new(x, i)))
				pixel_put(&cfg->images[cfg->img], x, i, cfg->color_floor);
			i++;
		}
}
