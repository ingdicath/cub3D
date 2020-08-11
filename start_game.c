/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_game.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/06 14:19:42 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/11 17:12:17 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

/*
** aqui podria incluirse destroy window cuando screenshot no se necesita
*/

void		ft_reset_movements(t_movements *movements)
{
	movements->move_front = 0;
	movements->move_back = 0;
	movements->move_right = 0;
	movements->move_left = 0;
	movements->rotate_right = 0;
	movements->rotate_left = 0;
}

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

int	ft_play_game(int keycode, t_game *game, t_map map)
{
	return (0);
}


/*
** - texture->step_size = How much to increase the texture coordinate
**	 per screen pixel.
** - texture->position = Starting texture coordinate.
**
*/
// ////////////////////////////11 aug ////////////////////////////////////////

void ft_draw_wall(t_ray *ray, t_position start, t_texture *texture)  // name of function render wall??
{
	int y;
	int color;
	t_screen resolution;

	texture->step_size = 1.0 * texture->width / ray->line_height;
	texture->position = (ray->draw_start - resolution.height / 2 +
		ray->line_height / 2) * texture->step_size;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		texture->coordinate.col = texture->position & (texture->height - 1);
		texture->position += texture->step_size;
		//color = (unsigned int)(texture->height * texture->coordinate.col + texture->coordinate.row);
		// funcion que llama las texturas
		if (ray->side == 1)
			color = (color >> 1) & 8355711; //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
 		//buffer[y][x] = color;
		y++;
	}
}



// ////////////////////////////11 aug ////////////////////////////////////////

// void	ft_ray_buffer(t_ray *ray)
// {

// }


/*
** Draw the pixels of the stripe as a vertical line.
** - ray->wall_x = where exactly the wall was hit. This is required to know 
** 	 which x-coordinate of the texture we have to use.
** - tex->coordinate.row = is the x-coordinate of the texture, and this is calculated 
**	out of wall_x.
*/

//calculate value of wallX
//////////////////////////////11 aug ////////////////////////////////////////


void ft_wall_texture(t_ray *ray, t_position start, t_texture *tex)
{
	if (ray->side == 0)
		ray->wall_x = start.col + ray->perpwalldist * ray->dir.col;
	else
		ray->wall_x = start.row + ray->perpwalldist * ray->dir.row;
	ray->wall_x -= (int)ray->wall_x;
	tex->coordinate.row = int(ray->wall_x * double(tex->width));
	if (side == 0 && ray->dir.row > 0)
		tex->coordinate.row = tex->width - tex->coordinate.row - 1;
	if (side == 1 && ray->dir.row < 0)
		tex->coordinate.row = tex->width - tex->coordinate.row - 1;
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
	if (ray->draw_end >= ray->line_height)
	 	ray->draw_end = ray->line_height - 1;
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
		ray->perpwalldist = (ray->map.row - start.row +
			(1 - ray->step.row) / 2) / ray->dir.row;
	else
		ray->perpwalldist = (ray->map.col - start.col +
			(1 - ray->step.col) / 2) / ray->dir.col;
}

void	ft_perform_dda(t_map map, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedist.row < ray->sidedist.col)
		{
			ray->sidedist.row += ray->deltadist.row;
			ray->map.row += ray->step.row;
			ray->side = 0;
		}
		else
		{
			ray->sidedist.col += ray->deltadist.col;
			ray->map.col += ray->step.col;
			ray->side = 1;
		}
		if (map.data[ray->map.row][ray->map.col] > 0) /// revisar esta linea //(game->map.data[ray->map_x][ray->map_y] == '1') /// esto es el muro. porque es 1
			hit = 1;
	}
	ft_perp_wall_dist(ray, map.start_pos);
}

// Now, before the actual DDA can start, first stepX, stepY,
// and the initial sideDistX and sideDistY still have to be calculated.

void			ft_step_side_dist_init(t_position start, t_ray *ray)
{
	if (ray->dir.row < 0)
	{
		ray->step.row = -1;
		ray->sidedist.row = (start.row - ray->map.row) * ray->deltadist.row;
	}
	else
	{
		ray->step.row = 1;
		ray->sidedist.row = (ray->map.row + 1.0 - start.row) * ray->deltadist.row;
	}
	if (ray->dir.col < 0)
	{
		ray->step.col = -1;
		ray->sidedist.col = (start.col - ray->map.col) * ray->deltadist.col;
	}
	else
	{
		ray->step.col = 1;
		ray->sidedist.col = (ray->map.col + 1.0 - start.col) * ray->deltadist.col;
	}
}

t_ray				ft_render_map(t_game *game, t_screen resolution)
{
	int			x;
	t_ray		ray;

	x = 0;
	while (x < resolution.width)
	{
		ray.camera.row = 2 * x / (double)(resolution.width - 1);
		
		ray.dir.row = game->player.direction.row +
					game->player.plane.row * ray.camera.row;
		ray.dir.col = game->player.direction.col +
					game->player.plane.col * ray.camera.row;
		ray.map.row = (int)game->map.start_pos.row;
		ray.map.col = (int)game->map.start_pos.col;
		ray.deltadist.row = fabs(1 / ray.dir.row);
		ray.deltadist.col = fabs(1 / ray.dir.col);
		x++;
	}
	return (ray);
}

void		ft_reset_player(t_player *player)
{
	player->direction.row = 0;
	player->direction.col = 0;
	player->plane.row = 0;
	player->plane.col = 0;
	player->time = 0;
	player->old_time = 0;
}

int			ft_set_orientation(char orientation, t_player *player)
{
	ft_reset_player(player);
	if (orientation == 'N')
		player->direction.col = 1;
	else if (orientation == 'S')
		player->direction.col = -1;
	else if (orientation == 'W')
		player->direction.row = -1;
	else if (orientation == 'E')
		player->direction.row = 1;
	if (player->direction.col == 0)
		player->plane.col = 0.66;
	else
		player->plane.row = 0.66;
	return (1);
}

////////////////////////check como cargar las texturas, ver texture_wall in the tutorial
int			ft_set_texture(void *mlx, char *path, t_texture *texture)
{
	texture->width = 64;
	texture->height = 64;

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
	&& ft_set_texture(board->mlx, file.sprite_path, &board->east);
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
