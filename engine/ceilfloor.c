/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ceilfloor.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 13:11:40 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/17 15:26:28 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	render_floor_pixel(t_config *cfg, int x, int y)
{
	t_vector	t;
	t_texture	*tex;

	if (cfg->options[OPT_FLOORTEXT])
	{
		tex = &cfg->textures[TEXT_FLOOR];
		t.x = (int)(tex->width * (cfg->fc.floor.x -
			cfg->fc.cell.x)) & (tex->width - 1);
		t.y = (int)(tex->height * (cfg->fc.floor.y -
			cfg->fc.cell.y)) & (tex->height - 1);
		if (in_square(cfg->port_start, cfg->port_end, vector_new(x, y - 1)))
			pixel_put(&cfg->images[cfg->img], x, y - 1, get_px(*tex, t, 0));
	}
}

/*
** Resolve appropriate pixel color and write
*/

static void	render_ceil_pixel(t_config *cfg, int x, int y)
{
	t_vector	t;
	t_texture	*tex;

	cfg->fc.cell.x = (int)(cfg->fc.floor.x);
	cfg->fc.cell.y = (int)(cfg->fc.floor.y);
	cfg->fc.floor.x += cfg->fc.floorstep.x;
	cfg->fc.floor.y += cfg->fc.floorstep.y;
	if (cfg->options[OPT_CEILTEXT])
	{
		tex = &cfg->textures[TEXT_CEIL];
		t.x = (int)(tex->width * (cfg->fc.floor.x - cfg->fc.cell.x)) &
			(tex->width - 1);
		t.y = (int)(tex->height * (cfg->fc.floor.y - cfg->fc.cell.y)) &
			(tex->height - 1);
		if (in_square(cfg->port_start, cfg->port_end, vector_new(x, cfg->height
			- y - 1)))
			pixel_put(&cfg->images[cfg->img], x, cfg->height - y - 1,
				get_px(*tex, t, 0));
	}
	render_floor_pixel(cfg, x, y);
}

/*
** Iterate over the X pixel on screen, act accordingly
*/

static void	render_floor_line(t_config *cfg, int y)
{
	int			x;
	double		rowdist;
	t_player	*p;

	p = &cfg->player;
	cfg->fc.raydir0.x = p->dir.x - p->plane.x;
	cfg->fc.raydir0.y = p->dir.y - p->plane.y;
	cfg->fc.raydir1.x = p->dir.x + p->plane.x;
	cfg->fc.raydir1.y = p->dir.y + p->plane.y;
	rowdist = (0.5 * cfg->height) / (y - cfg->height / 2);
	cfg->fc.floorstep.x = rowdist * (cfg->fc.raydir1.x - cfg->fc.raydir0.x)
		/ cfg->width;
	cfg->fc.floorstep.y = rowdist * (cfg->fc.raydir1.y - cfg->fc.raydir0.y)
		/ cfg->width;
	cfg->fc.floor.x = p->pos.y + rowdist * cfg->fc.raydir0.x;
	cfg->fc.floor.y = p->pos.x + rowdist * cfg->fc.raydir0.y;
	x = 0;
	while (x < cfg->width)
	{
		if (y > cfg->height / 2)
			render_ceil_pixel(cfg, x, y);
		x++;
	}
}

/*
** Start ceil / floor render wrapper
*/

void		render_floor(t_config *cfg)
{
	int			y;

	y = 0;
	if ((cfg->options[OPT_FLOORTEXT] || cfg->options[OPT_FLOORTEXT]))
	{
		while (y <= cfg->height)
		{
			render_floor_line(cfg, y);
			y++;
		}
	}
}
