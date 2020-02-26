/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debugger.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 14:48:54 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/20 13:39:48 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <libft.h>
#include <stdlib.h>

/*
** Print string on screen with STRING as value
*/

static void	debugger_print_int(t_config *cfg, char *name, int value)
{
	int		color;
	char	*val;

	color = color_argb(0, 255, 255, 255);
	val = ft_itoa(value);
	mem_protect(cfg, val, "Could not allocate debugger string.");
	mlx_string_put(cfg->mlx, cfg->mlx_win, 5, 14 * cfg->debug_line,
		color, name);
	mlx_string_put(cfg->mlx, cfg->mlx_win, 12 * ft_strlen(name),
		14 * cfg->debug_line, color, val);
	cfg->debug_line++;
	free(val);
}

/*
** Debug menu wrapper [F3]
*/

void		debugger(t_config *cfg)
{
	t_player	*p;

	p = &cfg->player;
	if (cfg->debug == 0)
		return ;
	cfg->debug_line = 1;
	if (BONUS)
		debugger_print_int(cfg, "FPS:", (int)(1.0 / cfg->time_delta * 1000));
	debugger_print_int(cfg, "Player X:", (int)(p->pos.x * 1000));
	debugger_print_int(cfg, "Player Y:", (int)(p->pos.y * 1000));
	debugger_print_int(cfg, "Dir X:", (int)(p->dir.x * 1000));
	debugger_print_int(cfg, "Dir Y:", (int)(p->dir.y * 1000));
	debugger_print_int(cfg, "Plane X:", (int)(p->plane.x * 1000));
	debugger_print_int(cfg, "Plane Y:", (int)(p->plane.y * 1000));
	debugger_print_int(cfg, "Ray X:", (int)(p->ray.x * 1000));
	debugger_print_int(cfg, "Ray Y:", (int)(p->ray.y * 1000));
	debugger_print_int(cfg, "BONUS:", BONUS);
	debugger_print_int(cfg, "Floor Texture:", cfg->options[OPT_FLOORTEXT]);
	debugger_print_int(cfg, "Ceil Texture:", cfg->options[OPT_CEILTEXT]);
	debugger_print_int(cfg, "Sprite [Item]:", cfg->options[OPT_SPR_ITEM]);
	debugger_print_int(cfg, "Sprite [Coll]:", cfg->options[OPT_SPR_COLL]);
	debugger_print_int(cfg, "HUD:", cfg->options[OPT_TXT_HUD]);
	debugger_print_int(cfg, "TRAP:", cfg->options[OPT_TRAP]);
}
