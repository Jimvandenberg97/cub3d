/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/18 12:12:16 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/26 16:16:56 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include <libft.h>

void		ray_render(t_config *cfg, int x, t_player *p)
{
	int			tex;

	if (p->side % 2 == 0)
		p->pwalldist = (p->bx - p->pos.x + (1 - p->stepx) / 2) / p->ray.x;
	else
		p->pwalldist = (p->by - p->pos.y + (1 - p->stepy) / 2) / p->ray.y;
	cfg->zbuff[x] = p->pwalldist;
	p->lineheight = (int)(cfg->height / p->pwalldist);
	p->linestart = (p->lineheight * -1) / 2 + cfg->height / 2;
	if (p->linestart < 0)
		p->linestart = 0;
	p->lineend = p->lineheight / 2 + cfg->height / 2;
	if (p->lineend >= cfg->height)
		p->lineend = cfg->height - 1;
	if (p->side)
		tex = ((p->ray.y < 0) ? (TEXT_NO) : (TEXT_SO));
	else
		tex = ((p->ray.x < 0) ? (TEXT_WE) : (TEXT_EA));
	if (cfg->map[p->by][p->bx] == 'H' &&
		cfg->options[OPT_TXT_HWALL])
		tex = TEXT_HWALL;
	line_put(x, cfg, tex);
}

void		ray_calc(t_player *p, int x, double w)
{
	p->cam.x = 2 * x / w - 1;
	p->ray.y = p->dir.x + p->plane.x * p->cam.x;
	p->ray.x = p->dir.y + p->plane.y * p->cam.x;
	p->bx = (int)(p->pos.x);
	p->by = (int)(p->pos.y);
	p->deldist.x = fabs(1 / p->ray.x);
	p->deldist.y = fabs(1 / p->ray.y);
	p->hit = 0;
	p->stepx = (p->ray.x < 0) ? -1 : 1;
	p->sdist.x = (p->ray.x < 0)
			? (p->pos.x - p->bx) * p->deldist.x
			: (p->bx + 1.0 - p->pos.x) * p->deldist.x;
	p->stepy = (p->ray.y < 0) ? -1 : 1;
	p->sdist.y = (p->ray.y < 0)
			? (p->pos.y - p->by) * p->deldist.y
			: (p->by + 1.0 - p->pos.y) * p->deldist.y;
}

void		ray_cast(t_config *cfg, t_player *p)
{
	while (p->hit == 0)
	{
		if (p->sdist.x < p->sdist.y)
		{
			p->sdist.x += p->deldist.x;
			p->bx += p->stepx;
			p->side = 0;
		}
		else
		{
			p->sdist.y += p->deldist.y;
			p->by += p->stepy;
			p->side = 1;
		}
		if (ft_strchr(CSET_HIT, cfg->map[p->by][p->bx]) != NULL)
			p->hit = 1;
	}
}
