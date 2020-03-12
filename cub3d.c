/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/10 16:58:38 by jivan-de       #+#    #+#                */
/*   Updated: 2020/03/02 13:48:32 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "cub3d.h"

int		main(int argc, char *argv[])
{
	t_config	cfg;

	if (argc < 2)
		log_error(&cfg, "No config file provided.");
	if (argc > 3)
		log_error(&cfg, "Too many arguments");
	cfg.save = 0;
	if (argc == 3 && ft_strcmp(argv[2], "--save") == 0)
		cfg.save = 1;
	else if (argc == 3)
		log_error(&cfg, "Syntax: ./file <mapfile.cub> [--save]");
	config_parse(argv[1], &cfg);
	render_run(&cfg);
	return (0);
}
