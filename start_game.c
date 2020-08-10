/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_game.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   gamed: 2020/08/06 14:19:42 by dsalaman        #+#    #+#                 */
/*   Updated: 2020/08/07 16:59:51 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

/*
** aqui podria incluirse destroy window cuando screenshot no se necesita
** en el if, se podria colocar NULL en vez de ! ??
*/

int	ft_close_game(t_game *game)
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

int	ft_play_game(int keycode, t_game *game, t_map map)
{
	return (0);
}

/*
** Creating the raycasting
**
** @param t_game *game: 		the game instance
** @param t_screen: 			the resolution
** @return int:					1 is ok
*/

/////////////////////////////////// today /////////////////////////////////////

t_ray				ft_render_map(t_game *game, t_screen resolution)
{
	int			x;
	t_ray		ray;

	x = 0;
	while (x < resolution.width)
	{
		ray.camera_x = 2 * x / (double)(resolution.width - 1);
		
		ray.dir_x = game->player.direction_x +
					game->player.plane_x * ray.camera_x;
		ray.dir_y = game->player.direction_y +
					game->player.plane_y * ray.camera_x;
		ray.map_x = (int)game->map.start_pos.row;
		ray.map_y = (int)game->map.start_pos.column;
		ray.deltadist_x = fabs(1 / ray.dir_x);
		ray.deltadist_y = fabs(1 / ray.dir_y);
		x++;
	}
	return (ray);
}

/////////////////////////////////// today /////////////////////////////////////
// Now, before the actual DDA can start, first stepX, stepY,
// and the initial sideDistX and sideDistY still have to be calculated.

void			ft_step_side_dist_init(t_position start, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (start.row - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - start.row) * ray->deltadist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (start.column - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - start.column) * ray->deltadist_y;
	}
}

/////////////////////////////////// today /////////////////////////////////////
/*
** Creating the raycasting
 	int hit = 0; //was there a wall hit?
    int side; //was a NS or a EW wall hit?
	Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
    perpWallDist: the length of this line is the value to compute now, the distance 
    perpenducilar from the wall hit point to the camera plane instead of Euclidean
    distance to the player point, to avoid making straight walls look rounded.
*/

 

void ft_perpendicular_wall_dist(int side, t_ray *ray, t_position start)
{
	if(side == 0)
		ray->perpwalldist = (ray->map_x - start.row +
			(1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perpwalldist = (ray->map_y - start.column +
			(1 - ray->step_y) / 2) / ray->dir_y;
}

void	ft_perform_dda(t_map map, t_ray *ray)
{
	int	hit;
	int	side;

	hit = 0;
	side = 0;
	while (hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			side = 1;
		}
		if (map.data[ray->map_x][ray->map_y] > 0) /// revisar esta linea //(game->map.data[ray->map_x][ray->map_y] == '1') /// esto es el muro. porque es 1
			hit = 1;
	}
	ft_perpendicular_wall_dist(side, ray, map.start_pos);
}

void ft_screen_line_pixels_stripe (t_ray *ray)
{
	//Calculate height of line to draw on screen
      int lineHeight = (int)(h / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + h / 2;
      if(drawStart < 0)drawStart = 0;
      int drawEnd = lineHeight / 2 + h / 2;
      if(drawEnd >= h)drawEnd = h - 1;
}

/////////////////////////////////// today /////////////////////////////////////

int	ft_key_press(int keycode, t_game *game)
{
	// if (keycode == KEY_W)


	printf("auch%d\n ", keycode);
	return (0);
}

int	ft_key_release(int keycode, t_game *game)
{
	printf("fiiiiu\n");
	return (0);
}

int	ft_save_screen(t_game_file game_file)
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

int				ft_set_board(t_game_file file, t_game *game)
{
	t_texture	*data;

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

int			ft_set_all_textures(t_game_file file, t_board *board)
{
	int		result;

	result = ft_set_texture(board->mlx, file.no_path, &board->north)
	&& ft_set_texture(board->mlx, file.so_path, &board->south)
	&& ft_set_texture(board->mlx, file.we_path, &board->west)
	&& ft_set_texture(board->mlx, file.ea_path, &board->east)
	&& ft_set_texture(board->mlx, file.sprite_path, &board->east);
	return (result);
}

int			ft_set_texture(void *mlx, char *path, t_texture *texture)
{
	texture->image = mlx_xpm_file_to_image(mlx, path,
		&texture->width, &texture->height);
	if (texture->image == NULL)
		return (ft_put_error("invalid path for texture"));
	texture->address = mlx_get_data_addr(texture->image,
		&texture->bits_per_pixel, &texture->size_line, &texture->endian);
	if (texture->address == NULL)
		return (ft_put_error("image for texture failure"));
	return (1);
}

void		ft_reset_player(t_player *player)
{
	player->direction_x = 0;
	player->direction_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	player->time = 0;
	player->old_time = 0;
}

void		ft_reset_movements(t_movements *movements)
{
	movements->move_front = 0;
	movements->move_back = 0;
	movements->move_right = 0;
	movements->move_left = 0;
	movements->rotate_right = 0;
	movements->rotate_left = 0;

}


int			ft_set_orientation(char orientation, t_player *player)
{
	ft_reset_player(player);
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
	return (1);
}

int			ft_start_game(t_game_file file)
{
	t_game	game;
	t_board	*board;
	t_ray	ray;

	game.map = file.map;
	board = &game.board;
	if (!ft_set_board(file, &game))
		return (ft_put_error("set board failure"));
	ft_set_all_textures(file, &game.board);
	ft_set_orientation(game.map.orientation, &game.player);
	ray = ft_render_map(&game, file.resolution);
	ft_step_side_dist_init(game.map.start_pos, &ray);
	ft_perform_dda(game.map, &ray);

// eto podria ir en el main, se trata de eventos para keyboard y usar mlx
	mlx_hook(board->window, DESTROY, NOTIFY_MASK, &ft_close_game, &game);
	mlx_hook(board->window, PRESS, PRESS_MASK, &ft_key_press, &game);
	mlx_hook(board->window, RELEASE, RELEASE_MASK, &ft_key_release, &game);
	mlx_loop_hook(game.board.mlx, &ft_play_game, &game);
	mlx_loop(game.board.mlx);
	return (0);
}
