/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 16:30:21 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/19 15:20:07 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>

/*
** Ignore texture init if texture is not requested
*/

static int	optional(t_config *cfg, int x)
{
	int			i;
	const int	res[7][2] = {
		{TEXT_FLOOR, OPT_FLOORTEXT},
		{TEXT_CEIL, OPT_CEILTEXT},
		{TEXT_SPR_ITEM, OPT_SPR_ITEM},
		{TEXT_SPR_COLL, OPT_SPR_COLL},
		{TEXT_HWALL, OPT_TXT_HWALL},
		{TEXT_TRAP, OPT_TRAP},
		{TEXT_HUD, OPT_TXT_HUD}
	};

	i = 0;
	while (i < 7)
	{
		if ((x == res[i][0] && cfg->options[res[i][1]] == 0))
			return (1);
		i++;
	}
	return (0);
}

/*
** Initialize and allocate image spaces
*/

void		textures_init(t_config *cfg)
{
	int			i;

	i = 0;
	while (i < TEXT_COUNT)
	{
		if (optional(cfg, i))
		{
			i++;
			continue ;
		}
		cfg->textures[i].data.img = mlx_xpm_file_to_image(cfg->mlx,
			cfg->paths[i], &cfg->textures[i].width, &cfg->textures[i].height);
		mem_protect(cfg, cfg->textures[i].data.img, "Can't open texture file.");
		cfg->textures[i].data.addr = mlx_get_data_addr(
			cfg->textures[i].data.img, &cfg->textures[i].data.bits_per_pixel,
			&cfg->textures[i].data.line_length,
			&cfg->textures[i].data.endian);
		mem_protect(cfg, cfg->textures[i].data.addr,
			"Can't access data from texture object.");
		i++;
	}
}
