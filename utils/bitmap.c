/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bitmap.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/27 16:07:15 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/27 16:58:07 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <libft.h>
#include <fcntl.h>
#include <unistd.h>

static int
	image_size(int w, int h)
{
	int	per_line;

	per_line = w * BMP_BPP;
	if (per_line % 4 != 0)
		per_line += 4 - (per_line % 4);
	return (per_line * h);
}

static void
	bitmap_header(int fd, int w, int h)
{
	int total_size;

	write(fd, "BM", 2);
	total_size = BMP_HSIZE + image_size(w, h);
	write(fd, &total_size, 4);
	write(fd, "\0\0\0\0\x36\0\0\0\x28\0\0\0", 12);
	write(fd, &w, 4);
	write(fd, &h, 4);
	write(fd, "\x01\0\x18\0\0\0\0\0\0\0\0\0\0\0\0\
		\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 28);
}

static int
	bitmap_save(unsigned char *image, int h, int w, char *fname)
{
	unsigned char	padding[3];
	int				paddsize;
	int				imgfile;
	int				i;

	imgfile = open(fname, O_RDWR | O_CREAT | O_TRUNC, 0755);
	if (imgfile < 0)
		return (0);
	paddsize = (4 - (w * BMP_BPP) % 4) % 4;
	bitmap_header(imgfile, w, h);
	i = h - 1;
	while (i >= 0)
	{
		write(imgfile, image + (BMP_BPP * w * i), BMP_BPP * w);
		write(imgfile, padding, paddsize);
		i--;
	}
	close(imgfile);
	return (1);
}

static void
	bitmap_setpixel(t_config *cfg, t_vector pos, int z, unsigned char *image)
{
	unsigned char	*ptr;

	ptr = image + (int)(BMP_BPP * cfg->width * (int)pos.y) +
		((int)pos.x * BMP_BPP) + z;
	if (z == 0)
		*ptr = color_b((unsigned int)cfg->bmp_color);
	else if (z == 1)
		*ptr = color_g((unsigned int)cfg->bmp_color);
	else if (z == 2)
		*ptr = color_r((unsigned int)cfg->bmp_color);
}

void
	bitmap_export(t_config *cfg, char *fname)
{
	unsigned char	*image;
	t_vector		pos;
	int				ret;

	pos.y = 0;
	cfg->save = 0;
	image = ft_calloc(cfg->width * cfg->height, BMP_BPP);
	mem_protect(cfg, image, "Could not allocate bitmap memory.");
	while (pos.y < cfg->height)
	{
		pos.x = 0;
		while (pos.x < cfg->width)
		{
			cfg->bmp_color = get_screen_px(&cfg->images[0], pos.x, pos.y);
			bitmap_setpixel(cfg, pos, 0, image);
			bitmap_setpixel(cfg, pos, 1, image);
			bitmap_setpixel(cfg, pos, 2, image);
			pos.x++;
		}
		pos.y++;
	}
	ret = bitmap_save((unsigned char *)image, cfg->height, cfg->width, fname);
	if (!ret)
		log_error(cfg, "Could not save bitmap.");
}
