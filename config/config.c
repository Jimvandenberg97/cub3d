/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   config.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/16 14:10:42 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/20 13:55:58 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "cub3d.h"

/*
** Initialize config values where needed
*/

void	config_init(t_config *cfg)
{
	int		i;

	i = 0;
	cfg->width = -1;
	cfg->height = -1;
	while (i < TEXT_COUNT)
	{
		cfg->paths[i] = ft_strdup("\0");
		mem_protect(cfg, cfg->paths[i], "Could not allocate texture path.");
		i++;
	}
	cfg->color_floor = -1;
	cfg->color_ceil = -1;
}

/*
** [bool] - All required values set?
*/

int		config_ready(t_config *cfg)
{
	int	base;

	base = 0;
	base += (cfg->width == -1);
	base += (cfg->height == -1);
	base += (cfg->paths[0][0] == '\0');
	base += (cfg->paths[1][0] == '\0');
	base += (cfg->paths[2][0] == '\0');
	base += (cfg->paths[3][0] == '\0');
	base += (cfg->paths[4][0] == '\0');
	base += (cfg->color_floor == -1);
	base += (cfg->color_ceil == -1);
	return (base == 0);
}
