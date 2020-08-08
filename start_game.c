/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_game.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   gamed: 2020/08/06 14:19:42 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/07 16:59:51 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

// aqui podria incluirse destroy window cuando screenshot no se necesita
// en el if, se podria colocar NULL en vez de ! ??

int ft_close_game(t_game *game)
{
	printf("aqui toy\n");
	if (game->board.window)
		mlx_destroy_window(game->board.mlx, game->board.window);
	if (game->board.image)
		mlx_destroy_image(game->board.mlx, game->board.image);
	// if (game->texture.texture)
	// 	mlx_destroy_image(game->board.mlx, game->texture.texture);
	free(game);
	exit(0);
}

int ft_movements(int keycode, t_game *game)
{
		return (0);
}


int ft_key_press(int keycode, t_game *game)
{
	printf("auch%d\n ",keycode);

	return (0);
}

int ft_key_release(int keycode, t_game *game)
{
	printf("fiiiiu\n");
	return (0);
}

int ft_save_screen (t_game_file game_file)
{
	return (0);
}



// aqui podria incluirse destroy window cuando screenshot no se necesita

int ft_set_board(t_game_file file, t_game *game)
{
	game->board.mlx = mlx_init();
	if (game->board.mlx == NULL)
		return (ft_put_error("mlx connection failure"));
	game->board.window = mlx_new_window(game->board.mlx,
		file.resolution.width, file.resolution.height, "Welcome cub3d");
	if (game->board.window == NULL)
		return (ft_put_error("mlx window failure"));
	game->board.image = mlx_new_image(game->board.mlx,
		file.resolution.width, file.resolution.height);
	if (game->board.image == NULL)
		return (ft_put_error("mlx image failure"));
	game->board.address = mlx_get_data_addr(game->board.image,
		&game->board.bits_per_pixel, &game->board.line_length,
		&game->board.endian);
	if (game->board.address == NULL)			
		return (ft_put_error("mlx address image failure"));
	return (1);
}

int ft_set_textures(t_game_file file, t_game *game)
{
	

}

int ft_start_game(t_game_file file)
{
	t_game game;

	game.player.plane_x = 0;
	game.player.plane_y = 0.66;
	game.player.time = 0;
	game.player.old_time = 0;
	if (!ft_set_board(file, &game))
		return (ft_put_error("set board failure"));


 	// enum t_masks m;
// eto podria ir en el main, se trata de eventos para keyboard y usar mlx
	mlx_hook(game.board.window, DESTROY_NOTIFY, NOTIFY_MASK, &ft_close_game, &game);
	mlx_hook(game.board.window, KEY_PRESS, PRESS_MASK, &ft_key_press, &game);
	mlx_hook(game.board.window, KEY_RELEASE, RELEASE_MASK, &ft_key_release, &game);
	mlx_loop_hook(game.board.mlx, &ft_movements, &game);
	mlx_loop(game.board.mlx);

	return (0);
}


  


	