/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   spawn.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/27 13:27:04 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/05 16:47:22 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		spawn_set_ns(t_config *cfg, char c)
{
	if (c == 'N')
	{
		cfg->player.dir.x = -1;
		cfg->player.dir.y = 0;
		cfg->player.plane.x = 0;
		cfg->player.plane.y = 0.66;
	}
	else if (c == 'S')
	{
		cfg->player.dir.x = 1;
		cfg->player.dir.y = 0;
		cfg->player.plane.x = 0;
		cfg->player.plane.y = -0.66;
	}
}

static void		spawn_set_ew(t_config *cfg, char c)
{
	if (c == 'E')
	{
		cfg->player.dir.x = 0;
		cfg->player.dir.y = 1;
		cfg->player.plane.x = 0.66;
		cfg->player.plane.y = 0;
	}
	else if (c == 'W')
	{
		cfg->player.dir.x = 0;
		cfg->player.dir.y = -1;
		cfg->player.plane.x = -0.66;
		cfg->player.plane.y = 0;
	}
}

/*
** Calculate spawn rotation vectors
*/

void			spawn_setrotation(t_config *cfg, char c)
{
	spawn_set_ns(cfg, c);
	spawn_set_ew(cfg, c);
}
