/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/10 11:22:39 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/10 16:44:31 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Duplicate data from src sprite into dest sprite
*/

static void		sprite_dupe(t_sprite *dest, t_sprite *src)
{
	dest->pos.x = src->pos.x;
	dest->pos.y = src->pos.y;
	dest->tex = src->tex;
	dest->distance = src->distance;
	dest->hidden = src->hidden;
}

/*
** Swap 2 sprites in place
*/

static void		sprite_swap(t_sprite *left, t_sprite *right)
{
	t_sprite	temp;

	sprite_dupe(&temp, left);
	sprite_dupe(left, right);
	sprite_dupe(right, &temp);
}

/*
** Quicksort sorting algorithm
*/

void			quicksort(t_sprite *sprites, int first, int last)
{
	int			i;
	int			j;
	int			pivot;

	if (first < last)
	{
		pivot = first;
		i = first;
		j = last;
		while (i < j)
		{
			while (sprites[i].distance >= sprites[pivot].distance && i < last)
				i++;
			while (sprites[j].distance < sprites[pivot].distance)
				j--;
			if (i < j)
				sprite_swap(&sprites[i], &sprites[j]);
		}
		sprite_swap(&sprites[pivot], &sprites[j]);
		quicksort(sprites, first, j - 1);
		quicksort(sprites, j + 1, last);
	}
}
