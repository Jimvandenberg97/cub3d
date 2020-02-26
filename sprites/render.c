/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/10 13:25:33 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/26 18:03:07 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

static void		sprites_calc(t_config *cfg, t_srender *sr, int i)
{
	sr->spos.x = cfg->sprites[i].pos.y - cfg->player.pos.y;
	sr->spos.y = cfg->sprites[i].pos.x - cfg->player.pos.x;
	sr->invdet = 1.0 / (cfg->player.plane.x * cfg->player.dir.y -
		cfg->player.dir.x * cfg->player.plane.y);
	sr->transform.x = sr->invdet * (cfg->player.dir.y * sr->spos.x -
		cfg->player.dir.x * sr->spos.y);
	sr->transform.y = sr->invdet * (-cfg->player.plane.y * sr->spos.x +
		cfg->player.plane.x * sr->spos.y);
	sr->screenx = (int)((cfg->width / 2) * (1 + sr->transform.x /
		sr->transform.y));
	sr->height = abs((int)(cfg->height / (sr->transform.y)));
	sr->draw_start.y = sr->height * -1 / 2 + cfg->height / 2;
	if (sr->draw_start.y < 0)
		sr->draw_start.y = 0;
	sr->draw_end.y = sr->height / 2 + cfg->height / 2;
	if (sr->draw_end.y >= cfg->height)
		sr->draw_end.y = cfg->height - 1;
	sr->draw_start.x = sr->height * -1 / 2 + sr->screenx;
	if (sr->draw_start.x < 0)
		sr->draw_start.x = 0;
	sr->draw_end.x = sr->height / 2 + sr->screenx;
	if (sr->draw_end.x >= cfg->width)
		sr->draw_end.x = cfg->width - 1;
}

static void		sprites_draw_y(t_config *cfg, int i, t_srender *sr,
	t_vector *texpos)
{
	int			color;
	int			y;
	t_texture	*tex;

	tex = &cfg->textures[cfg->sprites[i].tex];
	y = sr->draw_start.y;
	while (y <= sr->draw_end.y)
	{
		texpos->y = (((y * 256 - cfg->height * 128 + sr->height * 128) *
			tex->height) / sr->height) / 256;
		if (texpos->y >= tex->height)
			texpos->y--;
		color = get_px(*tex, *texpos, 0);
		if ((color & 0x00FFFFFF) != 0 && in_square(cfg->port_start,
			cfg->port_end, vector_new(sr->x, y)))
			pixel_put(&cfg->images[cfg->img], sr->x, y, color);
		y++;
	}
}

static void		sprites_draw(t_config *cfg, t_srender *sr, int i)
{
	t_vector	texpos;

	sr->x = sr->draw_start.x;
	while (sr->x <= sr->draw_end.x)
	{
		if (sr->height < 1)
			sr->height = 1;
		texpos.x = (int)(256 * (sr->x - (sr->height * -1 / 2 + sr->screenx)) *
			cfg->textures[cfg->sprites[i].tex].width / sr->height) / 256;
		if (texpos.x >= cfg->textures[cfg->sprites[i].tex].width)
			texpos.x--;
		if (sr->transform.y > 0 && sr->x >= 0 && sr->x < cfg->width &&
			sr->transform.y < cfg->zbuff[sr->x])
			sprites_draw_y(cfg, i, sr, &texpos);
		sr->x++;
	}
}

void			sprites_render(t_config *cfg)
{
	int			i;
	t_srender	sr;

	i = 0;
	while (i < cfg->spritecnt)
	{
		if (!cfg->sprites[i].hidden)
		{
			sprites_calc(cfg, &sr, i);
			sprites_draw(cfg, &sr, i);
		}
		i++;
	}
}
