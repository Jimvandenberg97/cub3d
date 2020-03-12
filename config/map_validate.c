/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_validate.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoopman <jkoopman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/16 15:45:53 by jkoopman       #+#    #+#                */
/*   Updated: 2020/03/04 14:28:27 by jkoopman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stddef.h>
#include "cub3d.h"

static void			flood_fill(t_config *cfg, char **map, int x, int y)
{
	if (y > cfg->map_height - 1 || y < 0 || x < 0 ||
		x >= (int)ft_strlen(map[y]) || map[y][x] == ' ')
		log_error(cfg, "Invalid map.");
	if (map[y][x] == '1' || map[y][x] == '0')
		return ;
	if (map[y][x] != '$')
		return ;
	if (map[y][x] == '$')
		map[y][x] = '0';
	flood_fill(cfg, map, x + 1, y);
	flood_fill(cfg, map, x - 1, y);
	flood_fill(cfg, map, x, y + 1);
	flood_fill(cfg, map, x, y - 1);
	flood_fill(cfg, map, x - 1, y - 1);
	flood_fill(cfg, map, x + 1, y + 1);
	flood_fill(cfg, map, x + 1, y - 1);
	flood_fill(cfg, map, x - 1, y + 1);
}

/*
** Set spawnpoint in player object
*/

static void			map_setspawn(t_config *cfg, char *line, int row)
{
	int col;

	col = 0;
	while (line[col] != '\0')
	{
		if (ft_strchr(CSET_SPAWN, line[col]) != NULL)
		{
			spawn_setrotation(cfg, line[col]);
			line[col] = '0';
			break ;
		}
		col++;
	}
	cfg->player.pos.x = col + 0.5f;
	cfg->player.pos.y = row + 0.5f;
}

/*
** Validate map edge
*/

static void			check_edge(t_config *cfg, int *row, int *col, char **map)
{
	while (map[*row] != NULL && map[*row][*col] == 16)
		(*row)++;
	if (map[*row] != NULL)
		log_error(cfg, "Data after map.");
	(*row)--;
}

/*
** Validate map charset, exit out if invalid character is found
*/

static void			map_charset(char **map, char *set, t_config *cfg)
{
	int		row;
	int		col;

	row = 0;
	while (map[row] != NULL)
	{
		col = 0;
		while (map[row] != NULL && map[row][col] != '\0')
		{
			if (ft_strchr(CSET_SPAWN, map[row][col]) != NULL)
			{
				if ((int)cfg->player.pos.x == 0 && (int)cfg->player.pos.y == 0)
					map_setspawn(cfg, map[row], row);
				else
					log_error(cfg, "Too many spawnpoints.");
			}
			if (ft_strchr(set, map[row][col]) == NULL && map[row][col] != 16)
				log_error(cfg, "Invalid character in map.");
			else if (map[row][col] == 16)
				check_edge(cfg, &row, &col, map);
			col++;
		}
		row++;
	}
}

/*
** Validation wrapper
*/

void				map_validate(t_config *cfg)
{
	char		**map_dup;
	int			x;
	int			y;

	map_charset(cfg->map, CSET_MAP, cfg);
	if (cfg->player.pos.x == 0 && cfg->player.pos.y == 0)
		log_error(cfg, "Illegal spawnpoint.");
	map_dup = ft_calloc(cfg->map_height + 1, sizeof(char *));
	mem_protect(cfg, map_dup, "Could not allocate map dupe.");
	y = 0;
	while (y < cfg->map_height)
	{
		x = 0;
		map_dup[y] = ft_strdup(cfg->map[y]);
		mem_protect(cfg, map_dup[y], "Map dupe malloc error.");
		while (map_dup[y][x])
		{
			map_dup[y][x] = map_dup[y][x] != '1' ? '$' : map_dup[y][x];
			x++;
		}
		y++;
	}
	flood_fill(cfg, map_dup, cfg->player.pos.x, cfg->player.pos.y);
	r_wipe(map_dup);
}
