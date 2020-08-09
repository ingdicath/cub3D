
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
	if (game->board.window)
		mlx_destroy_window(game->board.mlx, game->board.window);
	if (game->board.win_data.image)
		mlx_destroy_image(game->board.mlx, game->board.win_data.image);
	// if (game->texture.texture)
	// 	mlx_destroy_image(game->board.mlx, game->texture.texture);
	//free(game);
	exit(0);
}

int ft_play_game(int keycode, t_game *game, t_map map)
{
	





		return (0);
}

int ft_render_map(t_game *game, t_screen resolution)
{
	int x;
	double camera_x;
	double ray_dir_x;
	double ray_dir_y;

	x = 0;
	while (x < resolution.width)
	{
		camera_x = 2 * x / (double)(resolution.width - 1);
		ray_dir_x = game->player.direction_x + game->player.plane_x * camera_x;
		ray_dir_y = game->player.direction_y + game->player.plane_y * camera_x;


	}

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

/*
** Initializing the game board
**
** @param t_game_file file: 	the input file (e.g. "file.cub" validated)
** @param t_game *game: 		the game instance
**
** @return int:					1 is ok					

*/

int ft_set_board(t_game_file file, t_game *game)
{
	t_texture *data;

	data = &game->board.win_data;
	game->board.mlx = mlx_init();
	if (game->board.mlx == NULL)
		return (ft_put_error("mlx connection failure"));
	game->board.window = mlx_new_window(game->board.mlx,
		file.resolution.width, file.resolution.height, "Welcome cub3d");
	if (game->board.window == NULL)
		return (ft_put_error("mlx window failure"));
	data->image = mlx_new_image(game->board.mlx,
		file.resolution.width, file.resolution.height);

	if (data->image == NULL)
		return (ft_put_error("mlx image failure"));
	data->address = mlx_get_data_addr(data->image, &data->bits_per_pixel, 
		&data->size_line, &data->endian);
	if (data->address == NULL)			
		return (ft_put_error("mlx address image failure"));
	return (1);
}

int ft_set_all_textures(t_game_file file, t_board *board)
{
	int result;

	result = ft_set_texture(board->mlx, file.no_path, &board->north)
	&& ft_set_texture(board->mlx, file.so_path, &board->south)
	&& ft_set_texture(board->mlx, file.we_path, &board->west)
	&& ft_set_texture(board->mlx, file.ea_path, &board->east)
	&& ft_set_texture(board->mlx, file.sprite_path, &board->east);
	return (result);
}

int		ft_set_texture(void *mlx, char *path, t_texture *texture)
{
	texture->image = mlx_xpm_file_to_image(mlx, path,
		&texture->width, &texture->height);
	if (texture->image  == NULL)
		return (ft_put_error("invalid path for texture"));
	texture->address = mlx_get_data_addr(texture->image, 
		&texture->bits_per_pixel, &texture->size_line, &texture->endian);
	if (texture->address  == NULL)
		return (ft_put_error("image for texture failure"));
	return (1);
}

void ft_initialize_player(t_player *player)
{
	player->direction_x = 0;
	player->direction_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	player->time = 0;
	player->old_time = 0;
}

int ft_set_orientation(char orientation, t_player *player)
{
	ft_initialize_player(player);
	if (orientation == 'N')
		player->direction_y = 1;
	else if (orientation == 'S')
		player->direction_y = -1;
	else if (orientation == 'W')
		player->direction_x = -1;
	else if (orientation == 'E')
		player->direction_x = 1;
	if (player->direction_y == 0)
		player->plane_y = 0.66;
	else
		player->plane_x = 0.66;
	return(1);
}

int ft_start_game(t_game_file file)
{
	t_game game;
	t_board *board;

	game.map = file.map;
	board = &game.board;
	if (!ft_set_board(file, &game))
		return (ft_put_error("set board failure"));
	ft_set_all_textures(file, &game.board);
	ft_set_orientation(game.map.orientation, &game.player);


 	// enum t_masks m;
// eto podria ir en el main, se trata de eventos para keyboard y usar mlx
	mlx_hook(board->window, DESTROY, NOTIFY_MASK, &ft_close_game, &game);
	mlx_hook(board->window, PRESS, PRESS_MASK, &ft_key_press, &game);
	mlx_hook(board->window, RELEASE, RELEASE_MASK, &ft_key_release, &game);
	mlx_loop_hook(game.board.mlx, &ft_play_game, &game);
	mlx_loop(game.board.mlx);

//int	mlx_loop_hook (void *mlx_ptr, int (*funct_ptr)(), void *param);
	return (0);
}


  


	