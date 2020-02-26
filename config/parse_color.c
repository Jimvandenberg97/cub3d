/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_color.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 11:49:36 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/26 18:08:44 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <libft.h>
#include <stdlib.h>

/*
** Resolve colors from strings to integers
*/

static void	parse_layers(t_config *cfg, char **blocks, int *color)
{
	int		r;
	int		g;
	int		b;

	r = ft_atoi(blocks[0]);
	g = ft_atoi(blocks[1]);
	b = ft_atoi(blocks[2]);
	if (r > 255 || g > 255 || b > 255)
		log_error(cfg, "Invalid color layer value.");
	*color = color_argb(0, r, g, b);
	free(blocks[0]);
	free(blocks[1]);
	free(blocks[2]);
	free(blocks[3]);
	free(blocks);
}

static void	colors_validate(t_config *cfg, char **blocks)
{
	int		i;
	int		j;
	int		c;

	i = 0;
	while (blocks[i])
	{
		j = 0;
		while (blocks[i][j] == ' ')
			j++;
		c = j;
		while (ft_isdigit(blocks[i][j]))
			j++;
		if (c == j)
			log_error(cfg, "No number provided for color layer.");
		while (blocks[i][j] == ' ')
			j++;
		if (blocks[i][j] != '\0' && blocks[i][j] != ',')
			log_error(cfg, "Invalid color.");
		i++;
	}
	if (i != 3)
		log_error(cfg, "Invalid color layer count.");
}

/*
** Color parse wrapper & executer
*/

void		parse_color(t_config *cfg, char *line, int *color)
{
	char	**blocks;
	int		i;
	int		j;

	if (*color != -1)
		log_error(cfg, "Double color in config file.");
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == ',')
			j++;
		i++;
	}
	if (j != 2)
		log_error(cfg, "Invalid color level count.");
	blocks = ft_split(line, ',');
	mem_protect(cfg, blocks, "Could not allocate for colors.");
	colors_validate(cfg, blocks);
	parse_layers(cfg, blocks, color);
}
