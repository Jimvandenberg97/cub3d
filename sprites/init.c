/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 15:53:45 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/19 15:26:51 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <libft.h>

/*
** Sprite types init
*/

static void		sprites_setup(t_config *cfg)
{
	cfg->stypes[0].c = '2';
	cfg->stypes[0].tex = TEXT_SPR;
	cfg->stypes[0].enabled = 1;
	cfg->stypes[1].c = '3';
	cfg->stypes[1].tex = TEXT_SPR_ITEM;
	cfg->stypes[1].enabled = cfg->options[OPT_SPR_ITEM];
	cfg->stypes[2].c = '4';
	cfg->stypes[2].tex = TEXT_SPR_COLL;
	cfg->stypes[2].enabled = cfg->options[OPT_SPR_COLL];
	cfg->stypes[3].c = 'T';
	cfg->stypes[3].tex = TEXT_TRAP;
	cfg->stypes[3].enabled = cfg->options[OPT_TRAP];
}

/*
** Run all the first sprite controllers
*/

void			sprites_init(t_config *cfg)
{
	int		spos;

	spos = 0;
	sprites_setup(cfg);
	sprites_allocate(cfg);
	cfg->sprites = ft_calloc(cfg->spritecnt, sizeof(t_sprite));
	mem_protect(cfg, cfg->sprites, "Failed to allocate sprite memory.");
	sprites_save(cfg, &spos);
}
