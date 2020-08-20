/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_game.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/06 14:19:42 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/18 21:25:52 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

/*
** Flags
** 	- O_WRONLY: Open for writing only.
** 	- O_CREAT: the file shall be created if it does not exist.
** 	- O_TRUNC: truncating the file length to 0 if it does exist.
**
** mode_t: The Mode Bits for Access Permission
** It can set up with octal or with symbolic constants:
** 	1) 0777: Permissions read, write or execute, it should be in octal.
**	2) S_IRWXU: This is equivalent to ‘(S_IRUSR | S_IWUSR | S_IXUSR)’
*/

static void ft_write_int_bytes(int fd, int param)
{
	write(fd, &param, FOUR_BYTES);
}

static void ft_write_short_bytes(int fd, int param)
{	
	write(fd, &param, TWO_BYTES);
}

static void ft_write_char_zeros(int fd, int times)
{
	int i; 

	i = 0;
	while (i < times)
	{
		write(fd, "\0", ONE_BYTE);
		i++;
	}
}

void		ft_set_header_bitmap(int fd, t_board *board)
{
	int		file_size; 
	char	*file_type;

	file_type = "BM";
	file_size = board->resolution.width * board->resolution.height *
		(BITS_PER_PIXEL / 8) + FINAL_IMAGE_SIZE;
	write(fd, file_type, TWO_BYTES);
	ft_write_int_bytes(fd, file_size);
	ft_write_char_zeros(fd, RESERVED_1);
	ft_write_char_zeros(fd, RESERVED_2);
	ft_write_int_bytes(fd, FINAL_IMAGE_SIZE);
	ft_write_int_bytes(fd, INFO_HEADER);
	ft_write_int_bytes(fd, board->resolution.width);
	ft_write_int_bytes(fd, board->resolution.height);
	ft_write_short_bytes(fd, PLANE);
	ft_write_short_bytes(fd, BITS_PER_PIXEL);
	ft_write_char_zeros(fd, COMPRESSION);
	ft_write_char_zeros(fd, IMAGE_SIZE);
	ft_write_char_zeros(fd, X_PPM);
	ft_write_char_zeros(fd, Y_PPM);
	ft_write_char_zeros(fd, TOTAL_COLORS);
	ft_write_char_zeros(fd, IMPORTANT_COLORS);
}

void 		ft_put_pixel_bitmap(int fd, t_board *board)
{
	int		x;
	int		y;
	int     pos;
	char    *address;
	
	address = board->win_data.address;
	y = board->resolution.height - 1;  //porque tenemos que incluir el cero
	while (y >= 0)
	{
		x = 0;
		while (x < board->resolution.width)
		{
			pos = y * board->win_data.size_line +x *
					(board->win_data.bits_per_pixel / 8);
			write(fd, &address[pos], FOUR_BYTES);
			x++;
		}
		y--;
	}
}

void ft_take_screenshot(t_game_file file)
{
	t_game game;

	int fd;

	fd = open(SCREENSHOT, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR); //preguntar si es full permission o solo lectura y escritura o es 755?
	if (fd < 0)
		ft_put_error("File screenshot cannot open");
	
	ft_initialize(file, &game);
	ft_set_header_bitmap(fd, &game.board);
	ft_put_pixel_bitmap(fd, &game.board);
	close(fd);
}

void		ft_reset_variables_game(t_board *board, t_player *player)
{
	board->mlx = NULL;
	board->window = NULL;
	board->win_data.image = NULL;
	board->north.address = NULL;
	board->south.address = NULL;
	board->west.address = NULL;
	board->east.address = NULL;
	board->sprite.address = NULL;
	player->move.move_front = 0;
	player->move.move_back = 0;
	player->move.move_right = 0;
	player->move.move_left = 0;
	player->move.turn_right = 0;
	player->move.turn_left = 0;
	// board->buffer = (double *)malloc(sizeof(double) * board->resolution.width);
	// if (board->buffer == NULL)
	// 	ft_putstr("Error, there is no buffer");
	// 	//PUT FUNCTION que haga free y muestre ERROR CON VOID
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

int ft_rgb_calculator(int r, int g, int b)
{
	return (r * RED_BIT + g * GREEN_BIT + b);
}

void ft_set_floor_ceiling_color(t_game_file file, t_board *board)
{
	board->floor = ft_rgb_calculator(file.floor.red, file.floor.green,
		file.floor.blue);
	board->ceiling = ft_rgb_calculator(file.ceiling.red, file.ceiling.green,
		file.ceiling.blue);
}

void ft_draw_floor_ceiling_color(t_board *board, int x)
{
	int y;
	
	y = 0;
	//printf("ceiling, floor %d %d\n", board->ceiling, board->floor);
	while(y < board->ray.draw_start)
	{
		ft_put_pixel(&board->win_data, x, y, board->ceiling);
		y++;
	}
	y = board->ray.draw_end;
	while(y < board->resolution.height)
	{
		ft_put_pixel(&board->win_data, x, y, board->floor);
		y++;
	}
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
	// //printf("auch%d\n ", keycode); //borrar
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
	// //printf("fiiiiu\n");
	return (0);
}

//move forward if no wall in front of you
void			ft_move_front(t_map map, t_player *player)
{
	// //printf("llo que quieras\n");
	t_position	new_pos;

	new_pos.x = player->current_pos.x + player->orientation.x * MOVE_SPEED;
	new_pos.y = player->current_pos.y + player->orientation.y * MOVE_SPEED;

	if (map.data[(int)new_pos.y][(int)player->current_pos.x] == '0') // Aca se revisa si el movimiento se sale del mapa 
		player->current_pos.y = new_pos.y;
	if (map.data[(int)player->current_pos.y][(int)new_pos.x] == '0') // si queremos el norte en el norte y es la primera posicion
		player->current_pos.x = new_pos.x;
}

//move backwards if no wall behind you
void			ft_move_back(t_map map, t_player *player)
{
	t_position	new_pos;

	new_pos.x = player->current_pos.x - player->orientation.x * MOVE_SPEED;
	new_pos.y = player->current_pos.y - player->orientation.y * MOVE_SPEED;
	if (map.data[(int)new_pos.y][(int)player->current_pos.x] == '0')
		player->current_pos.y = new_pos.y;
	if (map.data[(int)player->current_pos.y][(int)new_pos.x] == '0')
		player->current_pos.x = new_pos.x;
}

void			ft_move_right(t_map map, t_player *player)
{
	t_position	new_pos;
	new_pos.x = player->current_pos.x + player->plane.x * MOVE_SPEED;
	new_pos.y = player->current_pos.y + player->plane.y * MOVE_SPEED;
	if (map.data[(int)new_pos.y][(int)player->current_pos.x] == '0')
		player->current_pos.y = new_pos.y;
	if (map.data[(int)player->current_pos.y][(int)new_pos.x] == '0')
		player->current_pos.x = new_pos.x;
}

void			ft_move_left(t_map map, t_player *player)// tarea factorizar
{
	t_position	new_pos;
	new_pos.x = player->current_pos.x - player->plane.x * MOVE_SPEED;
	new_pos.y = player->current_pos.y - player->plane.y * MOVE_SPEED;
	if (map.data[(int)new_pos.y][(int)player->current_pos.x] == '0')
		player->current_pos.y = new_pos.y;
	if (map.data[(int)player->current_pos.y][(int)new_pos.x] == '0')
		player->current_pos.x = new_pos.x;
}
//rotate to the right
//both camera direction and camera plane must be rotated
void		ft_turn_left(t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->orientation.x;
	old_plane_x = player->plane.x;
	player->orientation.x = player->orientation.x * cos(-ROTATE_SPEED)
		- player->orientation.y * sin(-ROTATE_SPEED);
	player->orientation.y = old_dir_x * sin(-ROTATE_SPEED) +
		player->orientation.y * cos(-ROTATE_SPEED);
	player->plane.x = player->plane.x * cos(-ROTATE_SPEED)
		- player->plane.y * sin(-ROTATE_SPEED);
	player->plane.y = old_plane_x * sin(-ROTATE_SPEED) +
		player->plane.y * cos(-ROTATE_SPEED);
}

void	ft_turn_right(t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->orientation.x;
	old_plane_x = player->plane.x;
	player->orientation.x = player->orientation.x * cos(ROTATE_SPEED)
		- player->orientation.y * sin(ROTATE_SPEED);
	player->orientation.y = old_dir_x * sin(ROTATE_SPEED) +
		player->orientation.y * cos(ROTATE_SPEED);
	player->plane.x = player->plane.x * cos(ROTATE_SPEED)
		- player->plane.y * sin(ROTATE_SPEED);
	player->plane.y = old_plane_x * sin(ROTATE_SPEED) +
		player->plane.y * cos(ROTATE_SPEED);
}

int		ft_manage_movements(t_map map, t_player *player) //revisar si esta bien definida la posicion
{
	if (player->move.move_front == 1)
		ft_move_front(map, player);
	if (player->move.move_back == 1)
		ft_move_back(map, player);
	if (player->move.move_left == 1)
		ft_move_left(map, player);
	if (player->move.move_right == 1)
		ft_move_right(map, player);
	if (player->move.turn_left == 1)
		ft_turn_left(player);
	if (player->move.turn_right == 1)
		ft_turn_right(player);
	return (0);
}

t_texture		ft_get_textures(t_board board, t_ray *ray)
{
	t_texture	texture;
	if (ray->side == 0)
	{
		if (ray->dir.x < 0){
		////printf("choosed texture West address %p.width %d, texture height %d, bpp %d , size %d \n"  ,board.west.address, board.west.width, board.west.height, board.west.bits_per_pixel, board.west.size_line);
			texture = board.west;
		}
		else{
		////printf("choosed  texture Est address %p. width %d, texture height %d, bpp %d , size %d \n"  ,board.east.address, board.east.width, board.east.height, board.east.bits_per_pixel, board.east.size_line);
			texture = board.east;
		}
	}
	else
	{
		if (ray->dir.y < 0){
	////printf("choosed texture North address %p. width %d, texture height %d, bpp %d , size %d \n" ,board.north.address, board.north.width, board.north.height, board.north.bits_per_pixel, board.north.size_line);
			texture = board.north;
		}
		else{
	////printf("choosed texture south address %p. width %d, texture height %d, bpp %d , size %d \n"  ,board.south.address, board.south.width, board.south.height, board.south.bits_per_pixel, board.south.size_line);
			texture = board.south;
		}
	}
	return(texture);
}

int			ft_get_color(t_texture texture, t_ray ray)
{
	int		color;
	char	*dst;

	dst = texture.address + ((int)ray.tex.pos.y * texture.size_line +
		((int)ray.tex.pos.x * (texture.bits_per_pixel / 8)));
	color = *(unsigned int*)dst;
	return (color);
}

void		ft_put_pixel(t_texture *texture, int x, int y, int color)
{
	char	*dst;
	////printf("address %p y %d size %d  bits_per_pixel %d\n", texture->address, y, texture-> size_line, texture->bits_per_pixel);
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

void	ft_texture_color(t_ray *ray, t_board board, int x)// name of function render wall??
{
	int y;
	int color;
	t_texture texture;

	ray->tex.step = 1.0 * TEXTURE_HEIGHT / ray->line_height;
	ray->tex.start_pos = (ray->draw_start - board.resolution.height / 2 +
		ray->line_height / 2) * ray->tex.step;
	y = ray->draw_start;

	//printf("draw_start:%d ray->draw_end:%d, X:%d\n", ray->draw_start,ray->draw_end, x);
	while (y < ray->draw_end)
	{
		ray->tex.pos.y = (int)ray->tex.start_pos & (TEXTURE_HEIGHT - 1);
		ray->tex.start_pos += ray->tex.step;
		// color = (unsigned int)(texture->height * texture->pos.y + texture->pos.x);
		
		texture = ft_get_textures(board, ray);
		color = ft_get_color(texture,  *ray);
		// funcion que llama las texturas

		if (ray->side == 1)
			color = (color >> 1) & 8355711; //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		ft_put_pixel(&board.win_data, x, y, color);
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

void	ft_wall_texture(t_ray *ray, t_position current)
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

void	ft_screen_line_pixels_stripe(t_ray *ray, t_screen resolution)
{
	ray->line_height = (int)(resolution.height / ray->perpwalldist);
	ray->draw_start = -ray->line_height / 2 + resolution.height / 2;
	//(resolution.height / 2) - (ray->line_height / 2) ;
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

void	ft_perp_wall_dist(t_ray *ray, t_position current)
{
	if(ray->side == 0)
		ray->perpwalldist = (ray->map.x - current.x +
			(1 - ray->step.x) / 2) / ray->dir.x;
	else
		ray->perpwalldist = (ray->map.y - current.y +
			(1 - ray->step.y) / 2) / ray->dir.y;
	ray->perpwalldist = (ray->perpwalldist < 1)  ? 1 : ray->perpwalldist;
	//printf("Line he%f\n",  ray->perpwalldist);//borrar
}


/*
** map.data[y][x] in this order of x and y, North face up
**
*/


void	ft_perform_dda(t_map map, t_ray *ray)
{
	int	hit;
	int x;
	int y;

	hit = 0;
	while (hit == 0)
	{
		// //printf("Hit %d\n", hit);
		// //printf("antes valor de ray->sidedist.x  %f\n", ray->sidedist.x);
		// //printf("antes valor de ray->sidedist.y  %f\n", ray->sidedist.y);
		if (ray->sidedist.x < ray->sidedist.y)
		{
			ray->sidedist.x += ray->deltadist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			// //printf("No son iguales \n");
			ray->sidedist.y += ray->deltadist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		x = (int)ray->map.x;
		y = (int)ray->map.y;
		//printf("checking map  %d %d %c\n", x , y , map.data[x][y]);//borrar

		if (map.data[y][x] == '1') {
		/// revisar esta linea //(game->map.data[ray->map_x][ray->map_y] == '1') /// esto es el muro. porque es 1
		// //printf("jugo\n");
			hit = 1;
		}
	}
}
// Now, before the actual DDA can start, first stepX, stepY,
// and the initial sideDistX and sideDistY still have to be calculated.

void			ft_step_side_dist_init(t_position current, t_ray *ray)
{
	// //printf("ray->dir.x %f\n", ray->dir.x );
	// //printf("ray->dir.y %f\n", ray->dir.y );
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->sidedist.x = (current.x - ray->map.x) * ray->deltadist.x;
		//printf("Operation mapX %f, startX  %f , deltadist %f\n", ray->map.x,current.x,ray->deltadist.x);
		//printf("uno ray->sidedist.x  %f\n", ray->sidedist.x);
	}
	else
	{
		ray->step.x = 1;
		ray->sidedist.x = (ray->map.x + 1.0 - current.x) * ray->deltadist.x;
		//printf("Operation mapX %f, startX  %f , deltadist %f\n", ray->map.x,current.x,ray->deltadist.x);
		//printf("dos ray->sidedist.x  %f\n", ray->sidedist.x);
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
	// //printf("before dda ray->sidedist.x  %lf\n", ray->sidedist.x);
	// //printf("before dda ray->sidedist.y  %f\n", ray->sidedist.y);
}

//////////////////////////////// 14 ago /////////////////////////////
void	ft_set_ray_position(t_game *game, int x)  /// check this
{
	t_ray		*ray;

	ray = &game->board.ray;
	// //printf("loading player  %f %f\n", game->player.direction.x  ,game->player.direction.y);
	ray->camera_x = 2 * x / (double)game->board.resolution.width - 1;
	
	ray->dir.x = game->player.orientation.x +
			game->player.plane.x * ray->camera_x;
	ray->dir.y = game->player.orientation.y +
			game->player.plane.y * ray->camera_x;
	
	ray->map.x = (int)game->player.current_pos.x; // map x revisar valor entero
	ray->map.y = (int)game->player.current_pos.y;

	//printf("Ray dir pos  %f %f\n", ray->dir.x  , ray->dir.y); //borrar
	// printf("Ray map pos  %f %f\n", ray->map.x  , ray->map.y); //borrar

	ray->deltadist.x = fabs(1 / ray->dir.x);
	ray->deltadist.y = fabs(1 / ray->dir.y);
	////printf("loading delta  %f %f\n", ray->deltadist.x  , ray->deltadist.y);
}

void			ft_render_map(t_game *game)
{
	int			x;

	//printf("resoultion W%d, H%d\n", game->board.resolution.width, game->board.resolution.height); //borrar
	x = 0;
	while (x < game->board.resolution.width)
	{
		ft_set_ray_position(game, x); ////////////////////// OK2
		ft_step_side_dist_init(game->player.current_pos, &game->board.ray);//OK 
		ft_perform_dda(game->map, &game->board.ray);// OK
		ft_perp_wall_dist(&game->board.ray, game->player.current_pos); // OK
		ft_screen_line_pixels_stripe(&game->board.ray, game->board.resolution); // OK
		ft_wall_texture(&game->board.ray, game->player.current_pos); // REVISAR SI CAMBIA CONSTANTE POR TEXTURA
		ft_texture_color(&game->board.ray, game->board, x);
		ft_draw_floor_ceiling_color(&game->board, x);
		x++;
	}
	mlx_put_image_to_window(game->board.mlx, game->board.window,
		game->board.win_data.image, 0, 0);
	//timing for input and FPS counter
	//printf("Poniendo imagen %p %d\n",game->board.win_data.address, game->board.win_data.size_line ); //borrar
}

void		ft_reset_player(t_player *player)
{
	player->orientation.x = 0;
	player->orientation.y = 0;
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
	{
		player->orientation.y = -1;
		player->plane.x = 0.66;
	}
	else if (map.orientation == 'S')
	{
		player->orientation.y = 1;
		player->plane.x = -0.66;
	}
	else if (map.orientation == 'W')
	{
		player->orientation.x = -1;
		player->plane.y = -0.66;
	}
	else if (map.orientation == 'E')
	{
		player->orientation.x = 1;
		player->plane.y = 0.66;
	}

	// Opcional (Magia!!!)
	player->current_pos.x += 0.5;
	player->current_pos.y += 0.5;


	// if (player->direction.y == 0)
	// 	player->plane.y = 0.66 ;
	// else
	// 	player->plane.x = 0.66 ;
	return (1);
}

////////////////////////check como cargar las texturas, ver texture_wall in the tutorial
int			ft_set_texture(void *mlx, char *path, t_texture *texture)
{
	//printf("%s\n", path); //borrar
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

int				ft_set_board(t_board *board)
{
	t_texture	*data;

	//printf("init resolution w:%d h:%d\n", board->resolution.width, board->resolution.height); //borrar
	data = &board->win_data;
	board->mlx = mlx_init();
	if (board->mlx == NULL)
		return (ft_put_error("mlx connection failure"));
	board->window = mlx_new_window(board->mlx,
		board->resolution.width, board->resolution.height, "Welcome");
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

int	ft_is_moving(t_movements move)
{
	return (move.move_front || move.move_back || move.move_left
		|| move.move_right || move.turn_right || move.turn_left);
}

int	ft_play_game(t_game *game)
{
	if (ft_is_moving(game->player.move))
	{
		ft_manage_movements(game->map, &game->player);
		ft_render_map(game);
		// printf("posicion %f %f\n", game->player.current_pos.x, game->player.current_pos.y);
		// printf("plano %f %f\n", game->player.plane.x, game->player.plane.y);
	}
	return (0);
}

int ft_initialize(t_game_file file, t_game *game)
{
	game->map = file.map;
	game->board.resolution = file.resolution;

	ft_reset_variables_game(&game->board, &game->player);
	if (!ft_set_board(&game->board))
		ft_put_error("set board failure"); // ok
	ft_set_floor_ceiling_color(file, &game->board);//ok
	ft_set_all_textures(file, &game->board); //ok
	ft_set_orientation(game->map, &game->player);
	ft_render_map(game);
	return(1);
}

int			ft_start_game(t_game_file file)
{
	t_game	game;

	ft_initialize(file, &game);
	mlx_hook(game.board.window, DESTROY, NOTIFY_MASK, &ft_close_game, &game);
	mlx_hook(game.board.window, PRESS, PRESS_MASK, &ft_key_press, &game);
	mlx_hook(game.board.window, RELEASE, RELEASE_MASK, &ft_key_release, &game);
	mlx_loop_hook(game.board.mlx, &ft_play_game, &game);
	mlx_loop(game.board.mlx);
	return (0);
}
