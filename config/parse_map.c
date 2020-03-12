/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoopman <jkoopman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 19:31:05 by jkoopman       #+#    #+#                */
/*   Updated: 2020/03/04 14:20:47 by jkoopman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <libft.h>
#include <stdlib.h>

/*
** Allocate memoryblock for the map
*/

static void	map_alloc(char **map, t_config *cfg)
{
	int pos;

	pos = 0;
	while (map[pos] != NULL)
	{
		cfg->map[pos] = ft_strdup(map[pos]);
		mem_protect(cfg, cfg->map[pos], "Failed to allocate memory for map.");
		pos++;
	}
	cfg->map[pos] = NULL;
}

/*
** Map saver wrapper
*/

void		parse_map(char **map, t_config *cfg)
{
	int		pos;

	pos = 0;
	while (map[pos] != NULL)
		pos++;
	cfg->map_height = pos;
	cfg->map = (char **)ft_calloc((pos + 1), (sizeof(char *)));
	mem_protect(cfg, cfg->map, "Failed to allocate map.");
	map_alloc(map, cfg);
}
