/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   finalize.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/28 16:53:23 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/20 13:56:48 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <unistd.h>

void	cleanup(t_config *cfg)
{
	if (cfg->mlx != NULL)
	{
		if (cfg->images[0].img != NULL)
			mlx_destroy_image(cfg->mlx, cfg->images[0].img);
		if (cfg->images[1].img != NULL)
			mlx_destroy_image(cfg->mlx, cfg->images[1].img);
		if (cfg->mlx_win != NULL)
			mlx_destroy_window(cfg->mlx, cfg->mlx_win);
	}
}

/*
** Cleanup before exiting
*/

int		finalize(t_config *cfg)
{
	log_close(cfg, "Bye bye :)");
	return (0);
}
