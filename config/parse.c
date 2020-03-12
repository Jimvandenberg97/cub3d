/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jkoopman <jkoopman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/14 14:37:25 by jkoopman       #+#    #+#                */
/*   Updated: 2020/02/26 17:54:36 by jkoopman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "cub3d.h"

/*
** Optional config elements
** [bool] - Is something done here?
*/

static int		element_options(char *line, t_config *cfg)
{
	if (ft_strncmp(line, "FT ", 2) == 0)
		parse_path(cfg, line + 2, &(cfg->paths[TEXT_FLOOR]));
	else if (ft_strncmp(line, "CT ", 2) == 0)
		parse_path(cfg, line + 2, &(cfg->paths[TEXT_CEIL]));
	else if (ft_strncmp(line, "SI ", 2) == 0)
		parse_path(cfg, line + 2, &(cfg->paths[TEXT_SPR_ITEM]));
	else if (ft_strncmp(line, "SC ", 2) == 0)
		parse_path(cfg, line + 2, &(cfg->paths[TEXT_SPR_COLL]));
	else if (ft_strncmp(line, "DH ", 2) == 0)
		parse_path(cfg, line + 2, &(cfg->paths[TEXT_HWALL]));
	else if (ft_strncmp(line, "XH ", 2) == 0)
		parse_path(cfg, line + 2, &(cfg->paths[TEXT_HUD]));
	else if (ft_strncmp(line, "XT ", 2) == 0)
		parse_path(cfg, line + 2, &(cfg->paths[TEXT_TRAP]));
	else
		return (0);
	cfg->options[OPT_FLOORTEXT] += (ft_strncmp(line, "FT ", 2) == 0);
	cfg->options[OPT_CEILTEXT] += (ft_strncmp(line, "CT ", 2) == 0);
	cfg->options[OPT_SPR_ITEM] += (ft_strncmp(line, "SI ", 2) == 0);
	cfg->options[OPT_SPR_COLL] += (ft_strncmp(line, "SC ", 2) == 0);
	cfg->options[OPT_TXT_HWALL] += (ft_strncmp(line, "DH ", 2) == 0);
	cfg->options[OPT_TXT_HUD] += (ft_strncmp(line, "XH ", 2) == 0);
	cfg->options[OPT_TRAP] += (ft_strncmp(line, "XT ", 2) == 0);
	return (1);
}

/*
** Check if we know the config element, if so, save it accordingly
*/

static void		element_switch(char *line, t_config *cfg)
{
	if (ft_strncmp(line, "R ", 1) == 0)
		parse_resolution(line + 1, cfg);
	else if (ft_strncmp(line, "NO ", 2) == 0)
		parse_path(cfg, line + 2, &(cfg->paths[TEXT_NO]));
	else if (ft_strncmp(line, "SO ", 2) == 0)
		parse_path(cfg, line + 2, &(cfg->paths[TEXT_SO]));
	else if (ft_strncmp(line, "WE ", 2) == 0)
		parse_path(cfg, line + 2, &(cfg->paths[TEXT_WE]));
	else if (ft_strncmp(line, "EA ", 2) == 0)
		parse_path(cfg, line + 2, &(cfg->paths[TEXT_EA]));
	else if (ft_strncmp(line, "S ", 1) == 0)
		parse_path(cfg, line + 2, &(cfg->paths[TEXT_SPR]));
	else if (ft_strncmp(line, "F ", 1) == 0)
		parse_color(cfg, line + 1, &(cfg->color_floor));
	else if (ft_strncmp(line, "C ", 1) == 0)
		parse_color(cfg, line + 1, &(cfg->color_ceil));
	else if (line[0] != 16 && ft_strchr(CSET_MAP, line[0]) == NULL)
		log_error(cfg, "Unknown config element.");
}

/*
** Parse elements
*/

static void		config_parse_settings(char *file, t_config *cfg)
{
	int		elem;
	char	**elements;

	elements = ft_split(file, '\n');
	free(file);
	mem_protect(cfg, elements, "Could not load config file.");
	elem = 0;
	while (elements[elem] != NULL && ft_strchr(CSET_MINIT,
		elements[elem][0]) == NULL)
	{
		if (!element_options(elements[elem], cfg))
			element_switch(elements[elem], cfg);
		elem++;
	}
	parse_map(&elements[elem], cfg);
	elem = 0;
	while (elements[elem] != NULL)
	{
		free(elements[elem]);
		elem++;
	}
	free(elements[elem]);
	free(elements);
}

/*
** Look for config elements and start resolver
*/

static void		config_parse_elements(int fd, t_config *cfg)
{
	char	*tmp;
	char	*file;
	int		ret;

	ret = 1;
	file = ft_strdup("");
	mem_protect(cfg, file, "Config prepare failed.");
	while (ret > 0)
	{
		ret = ft_get_next_line(fd, &tmp);
		if (ret == -1)
			log_error(cfg, "Reading from config file failed.");
		if (ft_strlen(tmp) == 0)
		{
			tmp = ft_strjoin_free1(tmp, "\n");
			mem_protect(cfg, tmp, "Line parsing failed. (1)");
			*tmp = 16;
		}
		tmp = ft_strjoin_free1(tmp, "\n");
		mem_protect(cfg, tmp, "Line parsing failed. (2)");
		file = ft_strjoin_free12(file, tmp);
		mem_protect(cfg, file, "Line parsing failed. (3)");
	}
	config_parse_settings(file, cfg);
}

/*
** Total parse wrapper
*/

void			config_parse(char *path, t_config *cfg)
{
	int			fd;
	char		*ptr;

	ptr = ft_strrchr(path, '.');
	if (!ptr || ft_strncmp(ptr, ".cub", 4) != 0)
		log_error(cfg, "Invalid file extension.");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		log_error(cfg, "Failed to open config.");
	config_init(cfg);
	config_parse_elements(fd, cfg);
	if (!config_ready(cfg))
		log_error(cfg, "Invalid config file. (Missing operands?)");
	map_validate(cfg);
	sprites_init(cfg);
}
