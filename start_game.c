/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_game.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/06 14:19:42 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/07 16:59:51 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

// aqui podria incluirse destroy window cuando screenshot no se necesita
// en el if, se podria colocar NULL en vez de ! ??

int ft_close_game(t_create *create)
{
	if (create->mlx.window)
		mlx_destroy_window(create->mlx.mlx, create->mlx.window);
	if (create->mlx.image)
		mlx_destroy_image(create->mlx.mlx, create->mlx.image);
	if (create->texture.texture)
		mlx_destroy_image(create->mlx.mlx, create->texture.texture);
	free(create);
	exit(0);
}


int ft_key_press(int keycode, t_create *create)
{
	
}




// aqui podria incluirse destroy window cuando screenshot no se necesita
// en el if, se podria colocar NULL en vez de ! ??
int ft_start_game(t_create *create)
{
	if (!(create->mlx.mlx = mlx_init()))
		return (ft_put_error("mlx connection failure"));
	if (!(create->mlx.window = mlx_new_window(create->mlx.mlx,
		create->screen.width, create->screen.height, "Welcome cub3d")))
		return (ft_put_error("mlx window failure"));
	if (!(create->mlx.image = mlx_new_image(create->mlx.mlx,
		create->screen.width, create->screen.height)))
		return (ft_put_error("mlx image failure"));
	if (!(create->mlx.address = mlx_get_data_addr(create->mlx.image,
		&create->mlx.bits_per_pixel, &create->mlx.line_length,
		&create->mlx.endian)))			
		return (ft_put_error("mlx address image failure"));
	
	return (0);
}



// eto podria ir en el main, se trata de eventos para keyboard y usar mlx
	mlx_hook(create->mlx.window, DESTROY_NOTIFY, 1L << 17, &ft_close_game, create);
	mlx_hook(create->mlx.window, KEY_PRESS, 1L << 0, &ft_key_press, create);
	mlx_hook(create->mlx.window, KEY_RELEASE, 1L << 1, &ft_key_release, create);
	mlx_loop_hook(create->mlx.mlx, /*agregar function para movimiento*/, create);
	mlx_loop(create->mlx.mlx);
	return (0);



	create->game.plane_x = 0;
	create->game.plane_y = 0.66;
	create->game.time = 0;
	create->game.old_time = 0;