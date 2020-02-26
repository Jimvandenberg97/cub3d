/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   memory.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/16 14:14:21 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/18 11:05:04 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "cub3d.h"

/*
** Auto malloc checker
*/

void	mem_protect(t_config *cfg, void *ptr, char *msg)
{
	if (ptr == NULL)
		log_error(cfg, msg);
}

void	r_wipe(char **data)
{
	int		i;

	i = 0;
	while (data[i])
	{
		free(data[i]);
		i++;
	}
	free(data[i]);
	free(data);
}
