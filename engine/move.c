/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 18:24:17 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/14 17:32:42 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void			move_forward(t_config *cfg)
{
	t_player	*p;
	t_hitbox	hb;
	t_vector	tmp;

	p = &cfg->player;
	vector_set(&tmp, p->pos);
	tmp.x += p->dir.y * cfg->speed_move;
	hb = hitbox_calc(cfg, tmp);
	if ((p->dir.y >= 0 && (hb.e + hb.ne + hb.se) == 0) ||
		(p->dir.y < 0 && (hb.w + hb.nw + hb.sw) == 0))
		p->pos.x += p->dir.y * cfg->speed_move;
	vector_set(&tmp, p->pos);
	tmp.y += p->dir.x * cfg->speed_move;
	hb = hitbox_calc(cfg, tmp);
	if ((p->dir.x <= 0 && (hb.n + hb.nw + hb.ne) == 0) ||
		(p->dir.x > 0 && (hb.s + hb.sw + hb.se) == 0))
		p->pos.y += p->dir.x * cfg->speed_move;
}

static void			move_back(t_config *cfg)
{
	t_player	*p;
	t_hitbox	hb;
	t_vector	tmp;

	p = &cfg->player;
	vector_set(&tmp, p->pos);
	tmp.x -= p->dir.y * cfg->speed_move;
	hb = hitbox_calc(cfg, tmp);
	if ((p->dir.y <= 0 && (hb.e + hb.ne + hb.se) == 0) ||
		(p->dir.y > 0 && (hb.w + hb.nw + hb.sw) == 0))
		p->pos.x -= p->dir.y * cfg->speed_move;
	vector_set(&tmp, p->pos);
	tmp.y -= p->dir.x * cfg->speed_move;
	hb = hitbox_calc(cfg, tmp);
	if ((p->dir.x >= 0 && (hb.n + hb.nw + hb.ne) == 0) ||
		(p->dir.x < 0 && (hb.s + hb.sw + hb.se) == 0))
		p->pos.y -= p->dir.x * cfg->speed_move;
}

static void			move_left(t_config *cfg)
{
	t_player	*p;
	t_vector	tmp;
	t_hitbox	hb;
	double		delta;

	p = &cfg->player;
	vector_set(&tmp, p->pos);
	delta = cos(acos(p->dir.x) + M_PI) * cfg->speed_move;
	tmp.x -= delta;
	hb = hitbox_calc(cfg, tmp);
	if ((p->dir.x <= 0 && (hb.nw + hb.w + hb.sw) == 0) ||
		(p->dir.x > 0 && (hb.ne + hb.e + hb.se) == 0))
		p->pos.x = tmp.x;
	vector_set(&tmp, p->pos);
	delta = cos(acos(p->dir.y) + M_PI) * cfg->speed_move;
	tmp.y += delta;
	hb = hitbox_calc(cfg, tmp);
	if ((p->dir.y >= 0 && (hb.nw + hb.n + hb.ne) == 0) ||
		(p->dir.y < 0 && (hb.sw + hb.s + hb.se) == 0))
		p->pos.y = tmp.y;
}

static void			move_right(t_config *cfg)
{
	t_player	*p;
	t_vector	tmp;
	t_hitbox	hb;
	double		delta;

	p = &cfg->player;
	vector_set(&tmp, p->pos);
	delta = cos(acos(p->dir.x) + M_PI) * cfg->speed_move;
	tmp.x += delta;
	hb = hitbox_calc(cfg, tmp);
	if ((p->dir.x >= 0 && (hb.nw + hb.w + hb.sw) == 0) ||
		(p->dir.x < 0 && (hb.ne + hb.e + hb.se) == 0))
		p->pos.x = tmp.x;
	vector_set(&tmp, p->pos);
	delta = cos(acos(p->dir.y) + M_PI) * cfg->speed_move;
	tmp.y -= delta;
	hb = hitbox_calc(cfg, tmp);
	if ((p->dir.y <= 0 && (hb.nw + hb.n + hb.ne) == 0) ||
		(p->dir.y > 0 && (hb.sw + hb.s + hb.se) == 0))
		p->pos.y = tmp.y;
}

/*
** Move wrapper
*/

void				move_run(t_config *cfg)
{
	double		oldspeed;

	oldspeed = cfg->speed_move;
	if ((cfg->keys.forward || cfg->keys.back) &&
		(cfg->keys.left || cfg->keys.right))
		cfg->speed_move *= 0.7071;
	if (cfg->keys.forward == 1)
		move_forward(cfg);
	if (cfg->keys.back == 1)
		move_back(cfg);
	if (cfg->keys.left == 1)
		move_left(cfg);
	if (cfg->keys.right == 1)
		move_right(cfg);
	cfg->speed_move = oldspeed;
}
