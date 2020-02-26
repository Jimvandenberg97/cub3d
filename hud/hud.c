/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hud.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 18:06:28 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/19 15:30:20 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				hud_viewport(t_config *cfg)
{
	t_vector	pos;
	t_vector	tpos;
	t_texture	tex;

	pos.y = 0;
	vector_set(&cfg->port_start, vector_new(0, 0));
	vector_set(&cfg->port_end, vector_new(cfg->width - 1, cfg->height - 1));
	tex = cfg->textures[TEXT_HUD];
	while (pos.y < cfg->height && cfg->options[OPT_TXT_HUD])
	{
		tpos.y = pos.y * tex.height / cfg->height;
		pos.x = 0;
		while (pos.x < cfg->width)
		{
			tpos.x = pos.x * tex.width / cfg->width;
			if (get_px(tex, vector_new(tpos.x, tpos.y), 0) == 0x00000000)
			{
				if (cfg->port_start.x == 0 && cfg->port_start.y == 0)
					vector_set(&cfg->port_start, pos);
				vector_set(&cfg->port_end, pos);
			}
			pos.x++;
		}
		pos.y++;
	}
}

static void			hud_scorebar(t_config *cfg)
{
	t_vector	start;
	t_vector	end;

	start.x = cfg->width - cfg->width / 7;
	start.y = cfg->height - cfg->height / 20;
	end.x = cfg->width - cfg->width / 32;
	end.y = cfg->height - cfg->height / 35;
	draw_square(cfg, vector_new(start.x - 1, start.y - 1),
		vector_new(end.x + 1, end.y + 1), 0x00696969);
	end.x = start.x + (end.x - start.x) * cfg->player.score;
	if (end.x - start.x > 0)
		draw_square(cfg, start, end, 0x0000FFFF);
}

static void			hud_healthbar(t_config *cfg)
{
	t_vector	start;
	t_vector	end;

	if (!cfg->options[OPT_TXT_HUD])
		return ;
	start.x = cfg->width - cfg->width / 7;
	start.y = (cfg->height - cfg->height / 20) - cfg->height / 20;
	end.x = cfg->width - cfg->width / 32;
	end.y = (cfg->height - cfg->height / 35) - cfg->height / 20;
	draw_square(cfg, vector_new(start.x - 1, start.y - 1),
		vector_new(end.x + 1, end.y + 1), 0x00696969);
	end.x = start.x + (end.x - start.x) * cfg->player.health;
	if (end.x - start.x > 0)
		draw_square(cfg, start, end, color_argb(0, 255 *
			(1 - cfg->player.health), 255 * cfg->player.health, 0));
	hud_scorebar(cfg);
}

void				hud_draw(t_config *cfg)
{
	t_vector	pos;
	t_vector	tpos;
	t_texture	tex;
	int			color;

	pos.y = 0;
	tex = cfg->textures[TEXT_HUD];
	while (pos.y < cfg->height && cfg->options[OPT_TXT_HUD])
	{
		tpos.y = pos.y * tex.height / cfg->height;
		pos.x = 0;
		while (pos.x < cfg->width)
		{
			if (!in_square(cfg->port_start, cfg->port_end, pos))
			{
				tpos.x = pos.x * tex.width / cfg->width;
				color = get_px(tex, vector_new(tpos.x, tpos.y), 0);
				if (color != 0x00000000)
					pixel_put(&cfg->images[cfg->img], pos.x, pos.y, color);
			}
			pos.x++;
		}
		pos.y++;
	}
	hud_healthbar(cfg);
}
