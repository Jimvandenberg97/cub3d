/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/20 19:01:44 by jivan-de       #+#    #+#                */
/*   Updated: 2020/03/02 13:49:07 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <math.h>
#include <libft.h>
#include <stdlib.h>
#include <time.h>

static void		run_functions(t_config *cfg)
{
	double		oldtime;

	if (BONUS)
	{
		oldtime = cfg->time_old;
		cfg->time_delta = ((double)clock() - oldtime) / 1000;
		cfg->time_old = (double)clock();
	}
	move_run(cfg);
	look_run(cfg);
	render_floor(cfg);
	sprites_distcalc(cfg);
	quicksort(cfg->sprites, 0, cfg->spritecnt - 1);
}

static void		render_image(t_config *cfg)
{
	sprites_render(cfg);
	if (cfg->portrender < 2 && cfg->options[OPT_TXT_HUD])
	{
		cfg->portrender++;
		hud_draw(cfg);
	}
	else if (!cfg->options[OPT_TXT_HUD])
		hud_draw(cfg);
	if (!cfg->save)
		mlx_put_image_to_window(cfg->mlx, cfg->mlx_win,
			cfg->images[cfg->img].img, 0, 0);
	debugger(cfg);
	if (cfg->save)
	{
		bitmap_export(cfg, BMP_EXPNAME);
		exit(EXIT_SUCCESS);
	}
	cfg->img = !cfg->img;
}

int				render_frame(t_config *cfg)
{
	int			x;
	t_player	*p;

	p = &cfg->player;
	run_functions(cfg);
	x = 0;
	while (x < cfg->width)
	{
		ray_calc(p, x, (double)(cfg->width));
		ray_cast(cfg, p);
		ray_render(cfg, x, p);
		x++;
	}
	render_image(cfg);
	return (0);
}

void			render_run(t_config *cfg)
{
	t_player	*p;

	cfg->mlx = mlx_init();
	mem_protect(cfg, cfg->mlx, "Could not init MLX.");
	if (!cfg->save)
	{
		cfg->mlx_win = mlx_new_window(cfg->mlx, cfg->width, cfg->height,
			"Wolfenstein, but not really...");
		mem_protect(cfg, cfg->mlx_win, "Could not init MLX window.");
	}
	engine_init(cfg);
	image_init(cfg, &cfg->images[0], cfg->mlx);
	image_init(cfg, &cfg->images[1], cfg->mlx);
	p = &cfg->player;
	cfg->speed_move = SET_SPEED_MOV;
	cfg->speed_rot = SET_SPEED_ROT;
	cfg->hb_size = SET_HBSIZE;
	textures_init(cfg);
	hud_viewport(cfg);
	mlx_loop_hook(cfg->mlx, render_frame, cfg);
	mlx_loop(cfg->mlx);
}
