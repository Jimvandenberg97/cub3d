/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bitmap.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/11 15:23:06 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/19 15:23:43 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <libft.h>
#include <fcntl.h>
#include <unistd.h>

static unsigned char
	*bitmap_header(int height, int width, int paddsize)
{
	static unsigned char	header[BMP_FHSIZE];
	int						fsize;

	fsize = BMP_FHSIZE + BMP_IHSIZE + (BMP_BPP * width + paddsize) * height;
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	header[2] = (unsigned char)(fsize);
	header[3] = (unsigned char)(fsize >> 8);
	header[4] = (unsigned char)(fsize >> 16);
	header[5] = (unsigned char)(fsize >> 24);
	header[10] = (unsigned char)(BMP_FHSIZE + BMP_IHSIZE);
	return (header);
}

static unsigned char
	*bitmap_infoheader(int height, int width)
{
	static unsigned char header[BMP_IHSIZE];

	header[0] = (unsigned char)(BMP_IHSIZE);
	header[4] = (unsigned char)(width);
	header[5] = (unsigned char)(width >> 8);
	header[6] = (unsigned char)(width >> 16);
	header[7] = (unsigned char)(width >> 24);
	header[8] = (unsigned char)(height);
	header[9] = (unsigned char)(height >> 8);
	header[10] = (unsigned char)(height >> 16);
	header[11] = (unsigned char)(height >> 24);
	header[12] = (unsigned char)(1);
	header[14] = (unsigned char)(BMP_BPP * 8);
	return (header);
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
	write(imgfile, bitmap_header(h, w, paddsize), BMP_FHSIZE);
	write(imgfile, bitmap_infoheader(h, w), BMP_IHSIZE);
	i = h;
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
			bitmap_setpixel(cfg, pos, 2, image);
			bitmap_setpixel(cfg, pos, 1, image);
			bitmap_setpixel(cfg, pos, 0, image);
			pos.x++;
		}
		pos.y++;
	}
	ret = bitmap_save((unsigned char *)image, cfg->height, cfg->width, fname);
	if (!ret)
		log_error(cfg, "Could not save bitmap.");
}
