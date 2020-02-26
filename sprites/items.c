/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   items.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/12 13:48:48 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/20 13:54:47 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "cub3d.h"

/*
** Yeet the sprite from the screen
*/

static void		sprite_yeet(t_config *cfg, int x, int y)
{
	int		i;

	i = 0;
	while (i < cfg->spritecnt)
	{
		if ((int)cfg->sprites[i].pos.x == x && (int)cfg->sprites[i].pos.y == y)
		{
			cfg->sprites[i].hidden = 1;
			cfg->map[y][x] = '0';
			return ;
		}
		i++;
	}
}

void			item_pickup(t_config *cfg, int x, int y)
{
	cfg->sprites[cfg->spritecnt - 1].hidden = 1;
	if (ft_strchr(CSET_SPR_T, cfg->map[y][x]) != NULL)
		cfg->player.health -= (double)1 / 3;
	else
		cfg->player.score += (double)1 / cfg->player.items;
	if (cfg->player.health < 0.3)
		log_close(cfg, "You ded :(");
	sprite_yeet(cfg, x, y);
	cfg->portrender = 0;
}
