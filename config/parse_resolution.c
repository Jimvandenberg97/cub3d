/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_resolution.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoopman <jkoopman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/14 18:36:26 by jkoopman       #+#    #+#                */
/*   Updated: 2020/02/26 17:36:16 by jkoopman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <libft.h>
#include <mlx.h>

/*
** [bool] - Resolution already previously set?
*/

static int	parse_res_set(t_config *cfg)
{
	return (cfg->width != -1 && cfg->height != -1);
}

/*
** Limit resolution to screen size and force it to be higher than 128 x 128
*/

static void	limit(t_config *cfg)
{
	int		w;
	int		h;

	if (!cfg->save)
	{
		mlx_get_screen_size(cfg->mlx, &w, &h);
		if (cfg->width > w)
			cfg->width = w;
		if (cfg->height > h - 45)
			cfg->height = h - 45;
	}
	if (cfg->width < 1 || cfg->height < 1)
		log_error(cfg, "Resolution has to be at least 1x1.");
	if (cfg->width > 16384 || cfg->height > 16384)
		log_error(cfg, "Resolution has reached MLX limit of 16384.");
}

/*
** Resolution parse wrapper
*/

void		parse_resolution(char *line, t_config *cfg)
{
	size_t		pos;

	pos = 0;
	while (line[pos] == ' ')
		pos++;
	if (parse_res_set(cfg))
		log_error(cfg, "Double resolution in config.");
	if (!ft_isdigit(line[pos]))
		log_error(cfg, "Invalid screen size.");
	cfg->width = ft_atoi(&line[pos]);
	while (ft_isdigit(line[pos]))
		pos++;
	while (line[pos] == ' ')
		pos++;
	if (!ft_isdigit(line[pos]))
		log_error(cfg, "Invalid screen size.");
	cfg->height = ft_atoi(&line[pos]);
	while (ft_isdigit(line[pos]))
		pos++;
	if (line[pos] != '\0')
		log_error(cfg, "Invalid screen size.");
	limit(cfg);
}
