/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/07 16:44:36 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/18 11:28:54 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "cub3d.h"

/*
** Resolve spritetype and save to list
*/

static void		sprite_resolve(t_config *cfg, t_stypes type, t_vector pos,
	int *spos)
{
	cfg->sprites[*spos].pos.x = pos.x + 0.5;
	cfg->sprites[*spos].pos.y = pos.y + 0.5;
	cfg->sprites[*spos].tex = type.tex;
	(*spos)++;
}

/*
** Is a sprite requested?
*/

static int		sprite_on(t_config *cfg, char c)
{
	int			i;

	i = 0;
	while (i < SPRITE_COUNT)
	{
		if (cfg->stypes[i].c == c)
			return (cfg->stypes[i].enabled);
		i++;
	}
	return (0);
}

/*
** Scan for sprites and interpret
*/

static int		sprites_scan(t_config *cfg, char *c, t_vector pos, int *spos)
{
	int			i;

	i = 0;
	while (i < SPRITE_COUNT)
	{
		if (cfg->stypes[i].c == *c)
		{
			if (ft_strchr(CSET_SPR_I, *c) != NULL &&
				ft_strchr(CSET_SPR_T, *c) == NULL)
				cfg->player.items++;
			if (cfg->stypes[i].enabled)
				sprite_resolve(cfg, cfg->stypes[i], pos, spos);
			return (cfg->stypes[i].enabled);
		}
		i++;
	}
	return (0);
}

/*
** Allocate sprite array
*/

void			sprites_allocate(t_config *cfg)
{
	int		x;
	int		y;
	int		cnt;

	y = 0;
	cnt = 0;
	while (y < cfg->map_height)
	{
		x = 0;
		while (x < (int)ft_strlen(cfg->map[y]))
		{
			if (ft_strchr(CSET_SPR, cfg->map[y][x]) != NULL)
			{
				if (sprite_on(cfg, cfg->map[y][x]))
					cnt++;
				else
					log_error(cfg,
						"Undefined sprite type used. (Missing texture?)");
			}
			x++;
		}
		y++;
	}
	cfg->spritecnt = cnt;
}

/*
** Save sprite array
*/

void			sprites_save(t_config *cfg, int *spos)
{
	int			x;
	int			y;
	t_vector	pos;

	y = 0;
	while (y < cfg->map_height)
	{
		x = 0;
		while (x < (int)ft_strlen(cfg->map[y]))
		{
			if (ft_strchr(CSET_SPR, cfg->map[y][x]) != NULL)
			{
				pos.x = x;
				pos.y = y;
				if (!sprites_scan(cfg, &cfg->map[y][x], pos, spos))
					log_error(cfg,
						"Undefined sprite type used. (Missing texture?)");
			}
			x++;
		}
		y++;
	}
}
