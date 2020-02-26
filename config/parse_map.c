/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 19:31:05 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/20 14:07:28 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <libft.h>
#include <stdlib.h>

/*
** [int] - Size of the map line (Without spaces)
*/

static int	linesize(char *line)
{
	int	cnt;

	cnt = 0;
	while (*line != '\0')
	{
		if (*line != ' ')
			cnt++;
		line++;
	}
	return (cnt);
}

/*
** Allocate memoryblock for the map
*/

static void	map_alloc(char **map, t_config *cfg)
{
	int pos;
	int i;
	int j;

	pos = 0;
	while (map[pos] != NULL)
	{
		i = 0;
		j = 0;
		cfg->map[pos] = malloc(linesize(map[pos]) + 1);
		mem_protect(cfg, cfg->map[pos], "Failed to allocate memory for map.");
		while (map[pos][j] != '\0')
		{
			if (map[pos][j] != ' ')
			{
				cfg->map[pos][i] = map[pos][j];
				i++;
			}
			j++;
		}
		cfg->map[pos][i] = '\0';
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
	cfg->map = (char **)malloc((pos + 1) * (sizeof(char *)));
	mem_protect(cfg, cfg->map, "Failed to allocate map.");
	map_alloc(map, cfg);
}
