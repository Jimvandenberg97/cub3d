/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   messages.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jivan-de <jivan-de@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/14 16:58:33 by jivan-de       #+#    #+#                */
/*   Updated: 2020/02/19 14:59:23 by jivan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include "cub3d.h"

/*
** Exit (With FAIL status)
*/

void		log_error(t_config *cfg, char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	cleanup(cfg);
	exit(EXIT_FAILURE);
}

/*
** Exit (With OK status)
*/

void		log_close(t_config *cfg, char *msg)
{
	ft_putstr_fd(msg, 1);
	ft_putstr_fd("\n", 1);
	cleanup(cfg);
	exit(EXIT_SUCCESS);
}
