/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bitmap.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/11 15:23:06 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/27 14:32:47 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "cub3d.h"

static int		image_size(int w, int h)
{
	int	per_line;

	per_line = w * 3;
	if (per_line % 4 != 0)
		per_line += 4 - (per_line % 4);
	return (per_line * h);
}

static void		write_header(int fd, int w, int h)
{
	int total_size;

	write(fd, "BM", 2);
	total_size = 54 + image_size(w, h);
	write(fd, &total_size, 4);
	write(fd, "\0\0\0\0\x36\0\0\0\x28\0\0\0", 12);
	write(fd, &w, 4);
	write(fd, &h, 4);
	write(fd, "\x01\0\x18\0\0\0\0\0\0\0\0\0\0\0\0\
		\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 28);
}

static void		write_rgb(int fd, t_config *cfg)
{
	int x;
	int y;
	int pad;
	int rgb;

	x = 0;
	y = cfg->height - 1;
	pad = (4 - (cfg->width * 3) % 4) % 4;
	while (y >= 0)
	{
		while (x < cfg->width)
		{
			rgb = get_screen_px(&cfg->images[0], x, y);
			write(fd, &rgb, 3);
			x++;
		}
		x = 0;
		write(fd, &x, pad);
		y--;
	}
}

void			bitmap_export(t_config *cfg, char *fname)
{
	int	fd;

	cfg->save = 0;
	fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (fd < 0)
		log_error(cfg, "Failed to open bitmap file.");
	write_header(fd, cfg->width, cfg->height);
	write_rgb(fd, cfg);
	close(fd);
}
