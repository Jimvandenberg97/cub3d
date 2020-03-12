/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 11:45:21 by jivan-de       #+#    #+#                */
/*   Updated: 2020/03/09 15:06:13 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <libft.h>

/*
** State defaults and initializers
*/

static void	defaults_init(t_config *cfg)
{
	cfg->keys.forward = 0;
	cfg->keys.back = 0;
	cfg->keys.left = 0;
	cfg->keys.right = 0;
	cfg->keys.lleft = 0;
	cfg->keys.lright = 0;
	cfg->img = 0;
	cfg->time_old = 0;
	cfg->player.hit = 0;
	cfg->player.side = 0;
	cfg->debug = 0;
	cfg->player.health = 1;
}

/*
** [HOOK] - Key DOWN event
*/

static int	key_down(int keycode, t_config *cfg)
{
	if (keycode == CUB_KEY_ESC)
		finalize(cfg);
	else if (keycode == CUB_KEY_FORWARD)
		cfg->keys.forward = 1;
	else if (keycode == CUB_KEY_BACK)
		cfg->keys.back = 1;
	else if (keycode == CUB_KEY_LEFT)
		cfg->keys.left = 1;
	else if (keycode == CUB_KEY_RIGHT)
		cfg->keys.right = 1;
	else if (keycode == CUB_KEY_LLEFT)
		cfg->keys.lleft = 1;
	else if (keycode == CUB_KEY_LRIGHT)
		cfg->keys.lright = 1;
	else if (keycode == CUB_KEY_F3)
		cfg->debug = !cfg->debug;
	else if (keycode == CUB_KEY_F12)
		bitmap_export(cfg, BMP_SCRNAME);
	return (0);
}

/*
** [HOOK] - Key UP event
*/

static int	key_up(int keycode, t_config *cfg)
{
	if (keycode == CUB_KEY_FORWARD)
		cfg->keys.forward = 0;
	else if (keycode == CUB_KEY_BACK)
		cfg->keys.back = 0;
	else if (keycode == CUB_KEY_LEFT)
		cfg->keys.left = 0;
	else if (keycode == CUB_KEY_RIGHT)
		cfg->keys.right = 0;
	else if (keycode == CUB_KEY_LLEFT)
		cfg->keys.lleft = 0;
	else if (keycode == CUB_KEY_LRIGHT)
		cfg->keys.lright = 0;
	else if (keycode == CUB_KEY_LRIGHT)
		cfg->keys.lright = 0;
	return (0);
}

/*
** Engine defaults
*/

void		engine_init(t_config *cfg)
{
	int		i;

	i = 0;
	defaults_init(cfg);
	if (!cfg->save)
	{
		mlx_hook(cfg->mlx_win, 2, 1L << 0, key_down, cfg);
		mlx_hook(cfg->mlx_win, 3, 1L << 1, key_up, cfg);
		mlx_hook(cfg->mlx_win, 17, 0L, finalize, cfg);
	}
	cfg->zbuff = ft_calloc(cfg->width, sizeof(double));
	mem_protect(cfg, cfg->zbuff, "Could not allocate depth buffer.");
}

/*
** Initialize MLX image
*/

void		image_init(t_config *cfg, t_data *img, void *mlx)
{
	img->img = mlx_new_image(mlx, cfg->width, cfg->height);
	mem_protect(cfg, img->img, "MLX Could not create image.");
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
		&img->line_length, &img->endian);
	mem_protect(cfg, img->addr, "MLX Could not translate image address.");
}
