/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   geometry.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 14:41:01 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/14 14:45:09 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "cub3d.h"

int		in_square(t_vector start, t_vector end, t_vector pos)
{
	return (pos.x >= start.x && pos.x <= end.x &&
		pos.y >= start.y && pos.y <= end.y);
}
