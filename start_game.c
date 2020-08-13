/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_game.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/06 14:19:42 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/13 16:55:06 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

/*
** aqui podria incluirse destroy window cuando screenshot no se necesita
*/

//////////////////////////// 12 aug /////////////////////////////////

void		ft_reset_variables_game(t_board *board, t_moves *moves)
{
	board->mlx = NULL;
	board->window = NULL;
	board->win_data.image = NULL;
	board->north.address = NULL;
	board->south.address = NULL;
	board->west.address = NULL;
	board->east.address = NULL;
	board->sprite.address = NULL;
	moves->move_front = 0;
	moves->move_back = 0;
	moves->move_right = 0;
	moves->move_left = 0;
	moves->turn_right = 0;
	moves->turn_left = 0;
	board->buffer = (double *)malloc(sizeof(double) * board->resolution.width);
	if (board->buffer == NULL)
		//PUT FUNCTION que haga free y muestre ERROR CON VOID
}

int	ft_close_game(t_game *game)
{
	// deberia liberar un buffer con los datos almacenados

	if (game->board.window)
		mlx_destroy_window(game->board.mlx, game->board.window);
	if (game->board.win_data.image)
		mlx_destroy_image(game->board.mlx, game->board.win_data.image);
	// if (game->texture.texture)
	// 	mlx_destroy_image(game->board.mlx, game->texture.texture);
	//free(game);
	exit(0);
}

int	ft_key_press(int keycode, t_game *game)
{
	if (keycode == ESC)
		ft_close_game(game); // create function
	if (keycode == KEY_W)
		game->player.move.move_front = 1;
	if (keycode == KEY_S)
		game->player.move.move_back = 1;
	if (keycode == KEY_A)
		game->player.move.move_left = 1;
	if (keycode == KEY_D)
		game->player.move.move_right = 1;
	if (keycode == RIGHT)
		game->player.move.turn_right = 1;
	if (keycode == LEFT)
		game->player.move.turn_left = 1;
	printf("auch%d\n ", keycode); //borrar
	return (0);
}

int	ft_key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->player.move.move_front = 0;
	if (keycode == KEY_S)
		game->player.move.move_back = 0;
	if (keycode == KEY_A)
		game->player.move.move_left = 0;
	if (keycode == KEY_D)
		game->player.move.move_right = 0;
	if (keycode == RIGHT)
		game->player.move.turn_right = 0;
	if (keycode == LEFT)
		game->player.move.turn_left = 0;
	printf("fiiiiu\n");
	return (0);
}

int	ft_save_screen(t_game_file game_file)
{
	return (0);
}

int	ft_play_game(t_game *game)
{
	t_board	*board;
	t_ray	ray;


	board = &game->board;
	ray = ft_render_map(game, board->resolution);
	ft_step_side_dist_init(game->map.start_pos, &ray);
	ft_perform_dda(game->map, &ray);
	ft_screen_line_pixels_stripe(&ray, board->resolution);
	ft_wall_texture(&ray, game->map.start_pos);
	ft_texture_color(&ray, board->resolution, *board);
	return (0);
}

int ft_choose_textures(t_board board, t_ray *ray)
{
	int 		color;
	char 		*path;
	t_texture 	texture;

	if (ray->side == 0)
	{
		if (ray->step.x < 0)
			texture = board.east;
		else
			texture = board.west;
	}
	else
	{
		if (ray->step.y < 0)
			texture = board.south;
		else
		  	texture = board.north;
	}
	path = texture.address + ((int)ray->tex.pos.y * texture.size_line +
		(int)ray->tex.pos.x * (texture.bits_per_pixel / 8));
	color = *(unsigned int*)path;
	return (color);
}




/////////////////////////13 ago//////////////////////

void ft_put_pixel(t_texture texture, int x, int y, int color)
{
	char *path;

	path = texture.address + (y * texture.size_line +
		(x* (texture.bits_per_pixel / 8)));
	color = *(unsigned int*)path;
}

/*
** - texture->step_size = How much to increase the texture coordinate
**	 per screen pixel.
** - texture->start_pos = Starting texture coordinate.
**
*/

void ft_texture_color(t_ray *ray, t_screen res, t_board board)// name of function render wall??
{
	int y;
	int color;

	ray->tex.step = 1.0 * TEXTURE_HEIGHT / ray->line_height;
	ray->tex.start_pos = (ray->draw_start - (res.height / 2) +
		(ray->line_height / 2)) * ray->tex.step;
	
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		ray->tex.pos.y = (int)ray->tex.start_pos & (TEXTURE_HEIGHT - 1);
		ray->tex.start_pos += ray->tex.step;
		// color = (unsigned int)(texture->height * texture->pos.y + texture->pos.x);
		color = ft_choose_textures(board, ray);
		// funcion que llama las texturas
		if (ray->side == 1)
			color = (color >> 1) & 8355711; //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
 		
 		buffer[y][x] = color; // ???
 		y++;
	}
}

/*
** Draw the pixels of the stripe as a vertical line.
** - ray->wall_x = where exactly the wall was hit. This is required to know 
** 	 which x-coordinate of the texture we have to use.
** - tex->pos.x = is the x-coordinate of the texture, and this is calculated 
**	out of wall_x.
*/

//calculate value of wallX
//////////////////////////////11 aug ////////////////////////////////////////


void ft_wall_texture(t_ray *ray, t_position start)
{

	if (ray->side == 0)
		ray->wall_x = start.y + ray->perpwalldist * ray->dir.y;
	else
		ray->wall_x = start.x + ray->perpwalldist * ray->dir.x;
	
	ray->wall_x -= floor(ray->wall_x);
	ray->tex.pos.x = (int)(ray->wall_x * (double)TEXTURE_WIDTH);
	
	if (ray->side == 0 && ray->dir.x > 0)
		ray->tex.pos.x = TEXTURE_WIDTH - ray->tex.pos.x - 1;
	if (ray->side == 1 && ray->dir.y < 0)
		ray->tex.pos.x = TEXTURE_WIDTH - ray->tex.pos.x - 1;
}

/*
** Calculate height of line to draw on screen the raycasting.
** Calculate lowest and highest pixel to fill in current stripe.
*/

void ft_screen_line_pixels_stripe(t_ray *ray, t_screen resolution)
{
	ray->line_height = (int)(resolution.height / ray->perpwalldist);
	ray->draw_start = -ray->line_height / 2 + resolution.height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + resolution.height / 2;
	if (ray->draw_end >= resolution.height)
	 	ray->draw_end = resolution.height - 1;
}

/*
** Creating the raycasting
 	int hit = 0; //was there a wall hit?
    int side; //was a NS or a EW wall hit?
	Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
    perpWallDist: the length of this line is the value to compute now, the distance 
    perpenducilar from the wall hit point to the camera plane instead of Euclidean
    distance to the player point, to avoid making straight walls look rounded.
*/

void ft_perp_wall_dist(t_ray *ray, t_position start)
{
	if(ray->side == 0)
		ray->perpwalldist = (ray->map.x - start.x +
			(1 - ray->step.x) / 2) / ray->dir.x;
	else
		ray->perpwalldist = (ray->map.y - start.y +
			(1 - ray->step.y) / 2) / ray->dir.y;
}

void	ft_perform_dda(t_map map, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedist.x < ray->sidedist.y)
		{
			ray->sidedist.x += ray->deltadist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist.y += ray->deltadist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;

		}
		printf("ray->map.x %f\n", ray->map.x); //borrar
  		printf("ray->map.x %f\n", ray->map.y); //borrar
		if (map.data[(int)ray->map.x][(int)ray->map.y] == '1') /// revisar esta linea //(game->map.data[ray->map_x][ray->map_y] == '1') /// esto es el muro. porque es 1
			hit = 1;
	}
	// ft_perp_wall_dist(ray, map.start_pos);  //13 ago: se comenta porque esta funcion va mas abajo
}

// Now, before the actual DDA can start, first stepX, stepY,
// and the initial sideDistX and sideDistY still have to be calculated.

void			ft_step_side_dist_init(t_position start, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->sidedist.x = (start.x - ray->map.x) * ray->deltadist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->sidedist.x = (ray->map.x + 1.0 - start.x) * ray->deltadist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->sidedist.y = (start.y - ray->map.y) * ray->deltadist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sidedist.y = (ray->map.y + 1.0 - start.y) * ray->deltadist.y;
	}
}

t_ray			ft_render_map(t_game *game, t_screen res, t_position start)
{
	int			x;
	t_ray		ray;

	x = 0;
	while (x < resolution.width)
	{
		ray.camera_x = 2 * x / (double)(res.width - 1);	
		ray.dir.x = game->player.direction.x +
					game->player.plane.x * ray.camera_x;
		ray.dir.y = game->player.direction.y +
					game->player.plane.y * ray.camera_x;
		ray.map.x = (int)game->map.start_pos.x;
		ray.map.y = (int)game->map.start_pos.y;
		ray.deltadist.x = fabs(1 / ray.dir.x);
		ray.deltadist.y = fabs(1 / ray.dir.y);

		ft_step_side_dist_init(start, &ray);  // revisar como se esta llamando la position
		// void			ft_step_side_dist_init(t_position start, t_ray *ray)

		ft_perform_dda(game->map, &ray);
		// void	ft_perform_dda(t_map map, t_ray *ray)

		ft_perp_wall_dist(&ray, game->map.start_pos);
		// void ft_perp_wall_dist(t_ray *ray, t_position start)

		ft_screen_line_pixels_stripe(&ray, res);
		// void ft_screen_line_pixels_stripe(t_ray *ray, t_screen resolution)

		ft_wall_texture(&ray, game->map.start_pos);
		// void ft_wall_texture(t_ray *ray, t_position start)

		ft_texture_color(&ray, res, game->board)
		// void ft_texture_color(t_ray *ray, t_screen res, t_board board)

		x++;
	}
	


	return (ray);
}

void		ft_reset_player(t_player *player)
{
	player->direction.x = 0;
	player->direction.y = 0;
	player->plane.x = 0;
	player->plane.y = 0;
	player->time = 0;
	player->old_time = 0;
}

int			ft_set_orientation(char orientation, t_player *player)
{
	ft_reset_player(player);
	if (orientation == 'N')
		player->direction.y = 1;
	else if (orientation == 'S')
		player->direction.y = -1;
	else if (orientation == 'W')
		player->direction.x = -1;
	else if (orientation == 'E')
		player->direction.x = 1;
	if (player->direction.y == 0)
		player->plane.y = 0.66;
	else
		player->plane.x = 0.66;
	return (1);
}

////////////////////////check como cargar las texturas, ver texture_wall in the tutorial
int			ft_set_texture(void *mlx, char *path, t_texture *texture)
{
	texture->width = TEXTURE_WIDTH;
	texture->height = TEXTURE_HEIGHT;

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

int			ft_set_all_textures(t_game_file file, t_board *board)
{
	int		result;

	result = ft_set_texture(board->mlx, file.no_path, &board->north)
	&& ft_set_texture(board->mlx, file.so_path, &board->south)
	&& ft_set_texture(board->mlx, file.we_path, &board->west)
	&& ft_set_texture(board->mlx, file.ea_path, &board->east)
	&& ft_set_texture(board->mlx, file.sprite_path, &board->sprite);
	return (result);
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

int			ft_start_game(t_game_file file)
{
	t_game	game;
	t_board	*board;
	t_ray	ray;

	game.map = file.map;
	board = &game.board;
	board->resolution = file.resolution;
	if (!ft_set_board(file, &game))
		return (ft_put_error("set board failure"));
	ft_set_all_textures(file, &game.board);
	ft_set_orientation(game.map.orientation, &game.player);
	ray = ft_render_map(&game, file.resolution);



	// ft_step_side_dist_init(game.map.start_pos, &ray);
	// ft_perform_dda(game.map, &ray);
	// ft_screen_line_pixels_stripe(&ray, file.resolution);
	// ft_wall_texture(&ray, file.map.start_pos);
	// ft_texture_color(&ray, file.resolution, *board);


// eto podria ir en el main, se trata de eventos para keyboard y usar mlx
	mlx_hook(board->window, DESTROY, NOTIFY_MASK, &ft_close_game, &game);
	mlx_hook(board->window, PRESS, PRESS_MASK, &ft_key_press, &game);
	mlx_hook(board->window, RELEASE, RELEASE_MASK, &ft_key_release, &game);
	mlx_loop_hook(game.board.mlx, &ft_play_game, &game);
	mlx_loop(game.board.mlx);
	return (0);
}
