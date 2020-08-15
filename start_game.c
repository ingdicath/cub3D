/* ************************************************************************** */
/*                                                                            */
/* asdffasdfasdfasd                                                       ::::::::            */
/*   start_game.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: edgarruiz <edgarruiz@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/14 19:00:22 by edgarruiz      #+#    #+#                */
/*   Updated: 2020/08/15 19:47:19 by edgarruiz     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_game.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/06 14:19:42 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/14 18:43:13 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

/*
** aqui podria incluirse destroy window cuando screenshot no se necesita
*/

//////////////////////////// 12 aug /////////////////////////////////

void		ft_reset_variables_game(t_board *board, t_movements *moves)
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
		ft_putstr("Error, there is no buffer");
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
	if (keycode == LEFT)
		game->player.move.turn_left = 0;
	if (keycode == RIGHT)
		game->player.move.turn_right = 0;
	printf("fiiiiu\n");
	return (0);
}

///////////////////////// 14 aug ////////////////////////////

   //move forward if no wall in front of you
void ft_move_front(t_game *game, t_position *start)
{
	t_position new_pos;

	new_pos.x = start->x + game->player.direction.x * MOVE_SPEED;
	new_pos.y = start->y + game->player.direction.y * MOVE_SPEED;

	if (game->map.data[(int)new_pos.x][(int)start->y] == '0')
		start->x += game->player.direction.x * MOVE_SPEED;
	if (game->map.data[(int)start->x][(int)new_pos.y] == '0')
		start->y += game->player.direction.y * MOVE_SPEED;
}

  //move backwards if no wall behind you
void ft_move_back(t_game *game, t_position *start)
{
	t_position new_pos;

	new_pos.x = start->x - game->player.direction.x * MOVE_SPEED;
	new_pos.y = start->y - game->player.direction.y * MOVE_SPEED;
	if (game->map.data[(int)new_pos.x][(int)start->y] == '0')
		start->x -= game->player.direction.x * MOVE_SPEED;
	if (game->map.data[(int)start->x][(int)new_pos.y] == '0')
		start->y += game->player.direction.y * MOVE_SPEED;
}

void ft_move_right(t_game *game, t_position *start) // revisar sentido, el ejemplo tenia los ejes [y][x]
{
	t_position new_pos;

	new_pos.x = start->x - game->player.direction.y * MOVE_SPEED;
	new_pos.y = start->y + game->player.direction.x * MOVE_SPEED;
	if (game->map.data[(int)new_pos.x][(int)start->y] == '0')
		start->x -= game->player.direction.y * MOVE_SPEED;
	if (game->map.data[(int)start->x][(int)new_pos.y] == '0')
		start->y += game->player.direction.x * MOVE_SPEED;
}

void ft_move_left(t_game *game, t_position *start) // revisar sentido, el ejemplo tenia los ejes [y][x]
{
	t_position new_pos;

	new_pos.x = start->x + game->player.direction.y * MOVE_SPEED;
	new_pos.y = start->y - game->player.direction.x * MOVE_SPEED;
	if (game->map.data[(int)new_pos.x][(int)start->y] == '0')
		start->x += game->player.direction.y * MOVE_SPEED;
	if (game->map.data[(int)start->x][(int)new_pos.y] == '0')
		start->y -= game->player.direction.x * MOVE_SPEED;
}
//rotate to the right
//both camera direction and camera plane must be rotated
void ft_turn_right(t_game *game)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = game->player.direction.x;
	old_plane_x = game->player.plane.x;
	game->player.direction.x = game->player.direction.x * cos(-ROTATE_SPEED)
		- game->player.direction.y * sin(-ROTATE_SPEED);
	game->player.direction.y = old_dir_x * sin(-ROTATE_SPEED) +
		game->player.direction.y * cos(-ROTATE_SPEED);
	game->player.plane.x = game->player.plane.x * cos(-ROTATE_SPEED)
		- game->player.plane.y * sin(-ROTATE_SPEED);
	game->player.plane.y = old_plane_x * sin(-ROTATE_SPEED) +
		game->player.plane.y * cos(-ROTATE_SPEED);
}

void ft_turn_left(t_game *game)  // revisar si deja compilar con valores negativos COS y SIN
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = game->player.direction.x;
	old_plane_x = game->player.plane.x;
	game->player.direction.x = game->player.direction.x * cos(ROTATE_SPEED)
		- game->player.direction.y * sin(ROTATE_SPEED);
	game->player.direction.y = old_dir_x * sin(ROTATE_SPEED) +
		game->player.direction.y * cos(ROTATE_SPEED);
	game->player.plane.x = game->player.plane.x * cos(ROTATE_SPEED)
		- game->player.plane.y * sin(-ROTATE_SPEED);
	game->player.plane.y = old_plane_x * sin(ROTATE_SPEED) +
		game->player.plane.y * cos(ROTATE_SPEED);
}


int ft_manage_movements(t_game *game, t_position *start) //revisar si esta bien definida la posicion
{
	if (game->player.move.move_front == 1)
		ft_move_front(game, start);
	if (game->player.move.move_back == 1)
		ft_move_back(game, start);
	if (game->player.move.move_left == 1)
		ft_move_left(game, start);
	if (game->player.move.move_right == 1)
		ft_move_right(game, start);
	if (game->player.move.turn_left == 1)
		ft_turn_left(game);
	if (game->player.move.turn_right == 1)
		ft_turn_right(game);

	return (0);

}



int	ft_save_screen(t_game_file game_file)
{
	return (0);
}



t_texture ft_get_textures(t_board board, t_ray *ray)
{
	
	t_texture 	texture;
	if (ray->side == 0)
	{
		if (ray->step.x < 0){
			printf("%s\n","oeste" );
			texture = board.west;
		}
		else{
			printf("%s\n","este" );
			texture = board.east;
		}
	}
	else
	{
		if (ray->step.y < 0){
			printf("%s\n","norte" );
			texture = board.north;
		}
		else{
			printf("%s\n","sur" );
		  	texture = board.south;
		}
	}
	return texture;
}


int ft_get_color(t_texture texture, t_ray ray)
{
	int 		color;
	char 		*dst;
	
	dst = texture.address + ((int)ray.tex.pos.y * texture.size_line +
		((int)ray.tex.pos.x * (texture.bits_per_pixel / 8)));

	color = *(unsigned int*)dst;
	return (color);
}

/////////////////////////13 ago//////////////////////

void ft_put_pixel(t_texture *texture, int x, int y, int color)
{
	char *dst;

	dst = texture->address + (y * texture->size_line +
		x * (texture->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

/*
** - texture->step_size = How much to increase the texture coordinate
**	 per screen pixel.
** - texture->start_pos = Starting texture coordinate.
**
*/

void ft_texture_color(t_ray *ray, t_board board, int x)// name of function render wall??
{
	int y;
	int color;
	t_texture texture;

	ray->tex.step = 1.0 * TEXTURE_HEIGHT / ray->line_height;
	ray->tex.start_pos = (ray->draw_start - (board.resolution.height / 2) +
		(ray->line_height / 2)) * ray->tex.step;
	
	y = ray->draw_start;


	while (y < ray->draw_end)
	{
		
		ray->tex.pos.y = (int)ray->tex.start_pos & (TEXTURE_HEIGHT - 1);
		ray->tex.start_pos += ray->tex.step;
		// color = (unsigned int)(texture->height * texture->pos.y + texture->pos.x);
		
		texture = ft_get_textures(board, ray);
		color = ft_get_color(texture,  *ray);
		// funcion que llama las texturas


		printf("Y . %d X %d,ray->draw_end %d\n", y,x, ray->draw_end);
		if (ray->side == 1)
			color = (color >> 1) & 8355711; //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
 		//ft_put_pixel(&texture, x, y, color);
 		
 		// buffer[y][x] = color; // ???
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


void ft_wall_texture(t_ray *ray, t_position current)
{

	if (ray->side == 0)
		ray->wall_x = current.y + ray->perpwalldist * ray->dir.y;
	else
		ray->wall_x = current.x + ray->perpwalldist * ray->dir.x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex.pos.x = (int)(ray->wall_x * (double)TEXTURE_WIDTH);
	if ((ray->side == 0 && ray->dir.x > 0)
		|| (ray->side == 1 && ray->dir.y < 0))
		ray->tex.pos.x = TEXTURE_WIDTH - ray->tex.pos.x - 1;
}

/*
** Calculate height of line to draw on screen the raycasting.
** Calculate lowest and highest pixel to fill in current stripe.
*/

void ft_screen_line_pixels_stripe(t_ray *ray, t_screen resolution)
{
	ray->line_height = (int)(resolution.height / ray->perpwalldist);
	ray->draw_start =  (resolution.height / 2) - (ray->line_height / 2) ;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->line_height / 2) + (resolution.height / 2);
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

void ft_perp_wall_dist(t_ray *ray, t_position current)
{
	if(ray->side == 0)
		ray->perpwalldist = (ray->map.x - current.x +
			(1 - ray->step.x) / 2) / ray->dir.x;
	else
		ray->perpwalldist = (ray->map.y - current.y +
			(1 - ray->step.y) / 2) / ray->dir.y;
}

void	ft_perform_dda(t_map map, t_ray *ray)
{
	int	hit;

	hit = 0;
	
	while (hit == 0)
	{
		// printf("Hit %d\n", hit);
		// printf("antes valor de ray->sidedist.x  %f\n", ray->sidedist.x);
		// printf("antes valor de ray->sidedist.y  %f\n", ray->sidedist.y);
		if (ray->sidedist.x < ray->sidedist.y)
		{
			ray->sidedist.x += ray->deltadist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			// printf("No son iguales \n");
			ray->sidedist.y += ray->deltadist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		int x = (int)ray->map.x;
		int y = (int)ray->map.y;
		printf("checking map  %d %d %c\n", x , y , map.data[x][y] );

		if (map.data[x][y] == '1') {
		/// revisar esta linea //(game->map.data[ray->map_x][ray->map_y] == '1') /// esto es el muro. porque es 1
			// printf("jugo\n");
			hit = 1;
		}
	}
}

// Now, before the actual DDA can start, first stepX, stepY,
// and the initial sideDistX and sideDistY still have to be calculated.

void			ft_step_side_dist_init(t_position current, t_ray *ray)
{
 	// printf("ray->dir.x %f\n", ray->dir.x );
 	// printf("ray->dir.y %f\n", ray->dir.y );

	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->sidedist.x = (current.x - ray->map.x) * ray->deltadist.x;
		// printf("uno ray->sidedist.x  %f\n", ray->sidedist.x);
	}
	else
	{
		ray->step.x = 1;
		ray->sidedist.x = (ray->map.x + 1.0 - current.x) * ray->deltadist.x;
		// printf("Operation mapX %f, startX  %f , deltadist %f\n", ray->map.x,start.x,ray->deltadist.x);
		 // printf("dos ray->sidedist.x  %f\n", ray->sidedist.x);
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->sidedist.y = (current.y - ray->map.y) * ray->deltadist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sidedist.y = (ray->map.y + 1.0 - current.y) * ray->deltadist.y;
	}
	 // printf("before dda ray->sidedist.x  %lf\n", ray->sidedist.x);
	 // printf("before dda ray->sidedist.y  %f\n", ray->sidedist.y);
}

//////////////////////////////// 14 ago /////////////////////////////
void	ft_set_ray_position(t_game *game,  int x)
{
	t_ray		*ray;

	ray = &game->board.ray ;

	// printf("loading player  %f %f\n", game->player.direction.x  ,game->player.direction.y);

	ray->camera_x = 2 * x / (double)(game->board.resolution.width - 1);	
	ray->dir.x = game->player.direction.x +
				game->player.plane.x * ray->camera_x;
	ray->dir.y = game->player.direction.y +
				game->player.plane.y * ray->camera_x;
	
	ray->map.x = (int)game->player.current_pos.x;
	ray->map.y = (int)game->player.current_pos.y;
	 
	 // printf("loading dir  %f %f\n", ray->dir.x  , ray->dir.y);
	 // printf("loading map  %f %f\n", ray->map.x  , ray->map.y);
	
	ray->deltadist.x = fabs(1 / ray->dir.x);
	ray->deltadist.y = fabs(1 / ray->dir.y);

	 // printf("loading delta  %f %f\n", ray->deltadist.x  , ray->deltadist.y);
}

void			ft_render_map(t_game *game)
{
	int			x;
	// t_ray		ray;

	// ray = game->board.ray;
	x = 0;
	while (x < game->board.resolution.width)
	{
		// ray.camera_x = 2 * x / (double)(game->board.resolution.width - 1);	
		// ray.dir.x = game->player.direction.x +
		// 			game->player.plane.x * ray.camera_x;
		// ray.dir.y = game->player.direction.y +
		// 			game->player.plane.y * ray.camera_x;
		// ray.map.x = (int)game->map.start_pos.x;
		// ray.map.y = (int)game->map.start_pos.y;
		// ray.deltadist.x = fabs(1 / ray.dir.x);
		// ray.deltadist.y = fabs(1 / ray.dir.y);
		ft_set_ray_position(game, x); ////////////////////// OK
		ft_step_side_dist_init(game->player.current_pos, &game->board.ray);  //OK 
		ft_perform_dda(game->map, &game->board.ray); // OK
		ft_perp_wall_dist(&game->board.ray, game->player.current_pos); // OK
		ft_screen_line_pixels_stripe(&game->board.ray, game->board.resolution); // OK
		ft_wall_texture(&game->board.ray, game->player.current_pos); // REVISAR SI CAMBIA CONSTANTE POR TEXTURA
		ft_texture_color(&game->board.ray, game->board, x); 
		x++;
	}
	 //timing for input and FPS counter

	mlx_put_image_to_window(game->board.mlx, game->board.window, 
		game->board.win_data.image, 0, 0);

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

int			ft_set_orientation(t_map map, t_player *player)
{
	ft_reset_player(player);
	player->current_pos = map.start_pos;

	if (map.orientation == 'N')
		player->direction.y = -1;
	else if (map.orientation == 'S')
		player->direction.y = 1;
	else if (map.orientation == 'W')
		player->direction.x = -1;
	else if (map.orientation == 'E')
		player->direction.x = 1;
	
	if (player->direction.y == 0)
		player->plane.y = -0.66 * player->direction.x;
	else
		player->plane.x = -0.66 * player->direction.y ;
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

	printf("texture West width %d, texture height %d, bpp %d , size %d \n" , board->west.width, board->west.height, board->west.bits_per_pixel, board->west.size_line);

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

int				ft_set_board(t_board *board)
{
	t_texture	*data;

	printf("init resolution w:%d h:%d\n", board->resolution.width, board->resolution.height);

	data = &board->win_data;
	board->mlx = mlx_init();
	if (board->mlx == NULL)
		return (ft_put_error("mlx connection failure"));
	board->window = mlx_new_window(board->mlx,
		board->resolution.width, board->resolution.height, "Welcome cub3d");
	if (board->window == NULL)
		return (ft_put_error("mlx window failure"));
	data->image = mlx_new_image(board->mlx,
		board->resolution.width, board->resolution.height);
	if (data->image == NULL)
		return (ft_put_error("mlx image failure"));
	data->address = mlx_get_data_addr(data->image, &data->bits_per_pixel,
		&data->size_line, &data->endian);
	if (data->address == NULL)
		return (ft_put_error("mlx address image failure"));
	return (1);
}

int	ft_play_game(t_game *game)
{
	//ft_render_map(game);
	
	return (0);
}

int			ft_start_game(t_game_file file)
{
	t_game	game;
	game.map = file.map;
	game.board.resolution = file.resolution;

	if (!ft_set_board(&game.board))
		return (ft_put_error("set board failure")); //OK

	ft_set_all_textures(file, &game.board); // OK
	ft_set_orientation(game.map, &game.player);  // OK
	ft_render_map(&game);
	// ft_step_side_dist_init(game.map.start_pos, &ray);
	// ft_perform_dda(game.map, &ray);
	// ft_screen_line_pixels_stripe(&ray, file.resolution);
	// ft_wall_texture(&ray, file.map.start_pos);
	// ft_texture_color(&ray, file.resolution, *board);

	mlx_hook(game.board.window, DESTROY, NOTIFY_MASK, &ft_close_game, &game);
	mlx_hook(game.board.window, PRESS, PRESS_MASK, &ft_key_press, &game);
	mlx_hook(game.board.window, RELEASE, RELEASE_MASK, &ft_key_release, &game);
	mlx_loop_hook(game.board.mlx, &ft_play_game, &game);
	mlx_loop(game.board.mlx);
	return (0);
}
