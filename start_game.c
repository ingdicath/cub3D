/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_game.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/06 14:19:42 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/06 14:54:29 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int ft_start_game(t_create *create)
{

	create->game.plane_x = 0;
	create->game.plane_y = 0.66;
	create->game.time = 0;
	create->game.old_time = 0;
	if (!(create->mlx.mlx = mlx_init()))
		ft_put_error("cannot initialize window");
	if (!(create->mlx.win = mlx_new_window(mlx, 800, 600, "Hello Pajarito");)


}