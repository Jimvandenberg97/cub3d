/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hitbox.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/24 14:14:56 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/12 13:56:21 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <libft.h>

/*
** Hit in given charset?
*/

static int			hit(t_config *cfg, double y, double x, char *cset)
{
	return (ft_strchr(cset, cfg->map[(int)y][(int)x]) != NULL);
}

/*
** Wall hitbox
*/

static t_hitbox		hitbox_wall(t_config *cfg, t_vector pos)
{
	t_hitbox	hb;

	hb.s = hit(cfg, (pos.y + cfg->hb_size), pos.x, CSET_COLL);
	hb.e = hit(cfg, pos.y, (pos.x + cfg->hb_size), CSET_COLL);
	hb.n = hit(cfg, (pos.y - cfg->hb_size), pos.x, CSET_COLL);
	hb.w = hit(cfg, pos.y, (pos.x - cfg->hb_size), CSET_COLL);
	hb.se = hit(cfg, (pos.y + cfg->hb_size), (pos.x + cfg->hb_size), CSET_COLL);
	hb.ne = hit(cfg, (pos.y - cfg->hb_size), (pos.x + cfg->hb_size), CSET_COLL);
	hb.nw = hit(cfg, (pos.y - cfg->hb_size), (pos.x - cfg->hb_size), CSET_COLL);
	hb.sw = hit(cfg, (pos.y + cfg->hb_size), (pos.x - cfg->hb_size), CSET_COLL);
	return (hb);
}

/*
** Sprite hitbox is different from wall hitbox
*/

static t_hitbox		hitbox_sprite(t_config *cfg, t_vector pos)
{
	t_hitbox	hb;

	hb.s = hit(cfg, (pos.y), pos.x, CSET_SPR_C);
	hb.e = hit(cfg, pos.y, (pos.x), CSET_SPR_C);
	hb.n = hit(cfg, (pos.y), pos.x, CSET_SPR_C);
	hb.w = hit(cfg, pos.y, (pos.x), CSET_SPR_C);
	hb.se = hit(cfg, (pos.y), (pos.x), CSET_SPR_C);
	hb.ne = hit(cfg, (pos.y), (pos.x), CSET_SPR_C);
	hb.nw = hit(cfg, (pos.y), (pos.x), CSET_SPR_C);
	hb.sw = hit(cfg, (pos.y), (pos.x), CSET_SPR_C);
	if (hb.n + hb.e + hb.s + hb.w + hb.se + hb.ne + hb.nw + hb.sw > 0 &&
		ft_strchr(CSET_SPR_I, cfg->map[(int)pos.y][(int)pos.x]) != NULL)
		item_pickup(cfg, pos.x, pos.y);
	return (hb);
}

/*
** Calculate hitbox values for given vector
*/

t_hitbox			hitbox_calc(t_config *cfg, t_vector pos)
{
	t_hitbox	hb;
	t_hitbox	hbw;
	t_hitbox	hbs;

	hbw = hitbox_wall(cfg, pos);
	hbs = hitbox_sprite(cfg, pos);
	hb.s = (hbw.s || hbs.s);
	hb.e = (hbw.e || hbs.e);
	hb.n = (hbw.n || hbs.n);
	hb.w = (hbw.w || hbs.w);
	hb.se = (hbw.se || hbs.se);
	hb.ne = (hbw.ne || hbs.ne);
	hb.nw = (hbw.nw || hbs.nw);
	hb.sw = (hbw.sw || hbs.sw);
	return (hb);
}
