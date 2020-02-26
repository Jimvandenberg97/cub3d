/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   distance.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/10 11:40:11 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/10 16:50:12 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Calculate & update distance in sprite array
*/

void		sprites_distcalc(t_config *cfg)
{
	int		i;

	i = 0;
	while (i < cfg->spritecnt)
	{
		cfg->sprites[i].distance = vector_distance(cfg->sprites[i].pos,
			cfg->player.pos);
		i++;
	}
}
