/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   look.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 18:32:48 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/05 16:43:21 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void			look_left(t_config *cfg)
{
	double		oldx;
	double		oldplanex;

	oldx = cfg->player.dir.x;
	cfg->player.dir.x = cfg->player.dir.x * cos(cfg->speed_rot) -
						cfg->player.dir.y * sin(cfg->speed_rot);
	cfg->player.dir.y = oldx * sin(cfg->speed_rot) + cfg->player.dir.y *
						cos(cfg->speed_rot);
	oldplanex = cfg->player.plane.x;
	cfg->player.plane.x = cfg->player.plane.x * cos(cfg->speed_rot) -
							cfg->player.plane.y * sin(cfg->speed_rot);
	cfg->player.plane.y = oldplanex * sin(cfg->speed_rot) +
							cfg->player.plane.y * cos(cfg->speed_rot);
}

static void			look_right(t_config *cfg)
{
	double		oldx;
	double		oldplanex;

	oldx = cfg->player.dir.x;
	cfg->player.dir.x = cfg->player.dir.x * cos(-cfg->speed_rot) -
						cfg->player.dir.y * sin(-cfg->speed_rot);
	cfg->player.dir.y = oldx * sin(-cfg->speed_rot) + cfg->player.dir.y *
						cos(-cfg->speed_rot);
	oldplanex = cfg->player.plane.x;
	cfg->player.plane.x = cfg->player.plane.x * cos(-cfg->speed_rot) -
							cfg->player.plane.y * sin(-cfg->speed_rot);
	cfg->player.plane.y = oldplanex * sin(-cfg->speed_rot) +
							cfg->player.plane.y * cos(-cfg->speed_rot);
}

/*
** Rotation wrapper
*/

void				look_run(t_config *cfg)
{
	if (cfg->keys.lleft == 1)
		look_left(cfg);
	if (cfg->keys.lright == 1)
		look_right(cfg);
}
