/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_path.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 11:25:50 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/20 13:55:26 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <libft.h>
#include <stdlib.h>

/*
** Validate & Store filepaths
*/

void		parse_path(t_config *cfg, char *line, char **var)
{
	while (*line == ' ')
		line++;
	if (ft_strlen(*var) != 0)
		log_error(cfg, "Double path element in config.");
	free(*var);
	*var = ft_strdup(line);
	mem_protect(cfg, *var, "Could not allocate path string.");
}
