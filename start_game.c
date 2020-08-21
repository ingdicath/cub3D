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

void		ft_set_header_bitmap(int fd, t_screen *screen)
{
	int		file_size; 
	char	*file_type;

	file_type = "BM";
	file_size = screen->win_size.width * screen->win_size.height *
		(BITS_PER_PIXEL / EIGHT_BITS) + FINAL_IMAGE_SIZE;
	write(fd, file_type, TWO_BYTES);
	ft_write_int_bytes(fd, file_size);
	ft_write_char_zeros(fd, RESERVED_1);
	ft_write_char_zeros(fd, RESERVED_2);
	ft_write_int_bytes(fd, FINAL_IMAGE_SIZE);
	ft_write_int_bytes(fd, INFO_HEADER);
	ft_write_int_bytes(fd, screen->win_size.width);
	ft_write_int_bytes(fd, screen->win_size.height);
	ft_write_short_bytes(fd, PLANE);
	ft_write_short_bytes(fd, BITS_PER_PIXEL);
	ft_write_char_zeros(fd, COMPRESSION);
	ft_write_char_zeros(fd, IMAGE_SIZE);
	ft_write_char_zeros(fd, X_PPM);
	ft_write_char_zeros(fd, Y_PPM);
	ft_write_char_zeros(fd, TOTAL_COLORS);
	ft_write_char_zeros(fd, IMPORTANT_COLORS);
}

void 		ft_put_pixel_bitmap(int fd, t_screen *screen)
{
	int		x;
	int		y;
	int     pos;
	char    *address;
	
	address = screen->win_data.address;
	y = screen->win_size.height - 1;  //porque tenemos que incluir el cero
	while (y >= 0)
	{
		x = 0;
		while (x < screen->win_size.width)
		{
			pos = y * screen->win_data.size_line +x *
					(screen->win_data.bits_per_pixel / EIGHT_BITS);
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
	
	ft_set_game(file, &game);
	ft_set_header_bitmap(fd, &game.screen);
	ft_put_pixel_bitmap(fd, &game.screen);
	close(fd);
}

void		ft_clean_game(t_screen *screen, t_player *player)
{
	screen->mlx = NULL;
	screen->window = NULL;
	screen->win_data.image = NULL;
	screen->north.address = NULL;
	screen->south.address = NULL;
	screen->west.address = NULL;
	screen->east.address = NULL;
	screen->sprite.address = NULL;
	player->move.front = 0;
	player->move.back = 0;
	player->move.right = 0;
	player->move.left = 0;
	player->rotate.right = 0;
	player->rotate.left = 0;
	player->orientation.x = 0;
	player->orientation.y = 0;
	player->plane.x = 0;
	player->plane.y = 0;
}


int	ft_close_game(t_game *game)
{
	if (game->screen.window)
		mlx_destroy_window(game->screen.mlx, game->screen.window);
	if (game->screen.win_data.image)
		mlx_destroy_image(game->screen.mlx, game->screen.win_data.image);
	exit(0);
}

int ft_rgb_calculator(int r, int g, int b)
{
	return (r * RED_BIT + g * GREEN_BIT + b);
}

void ft_set_floor_ceiling(t_game_file file, t_screen *screen)
{
	screen->floor = ft_rgb_calculator(file.floor.red, file.floor.green,
		file.floor.blue);
	screen->ceiling = ft_rgb_calculator(file.ceiling.red, file.ceiling.green,
		file.ceiling.blue);
}

void ft_draw_floor_ceiling(t_screen *screen, t_ray ray, int x)
{
	int y;
	
	y = 0;
	//printf("ceiling, floor %d %d\n", screen->ceiling, screen->floor);
	while(y < ray.draw_start)
	{
		ft_put_pixel(&screen->win_data, x, y, screen->ceiling);
		y++;
	}
	y = ray.draw_end;
	while(y < screen->win_size.height)
	{
		ft_put_pixel(&screen->win_data, x, y, screen->floor);
		y++;
	}
}

int	ft_key_press(int keycode, t_game *game)
{
	if (keycode == ESC)
		ft_close_game(game); // create function
	if (keycode == KEY_W)
		game->player.move.front = 1;
	if (keycode == KEY_S)
		game->player.move.back = 1;
	if (keycode == KEY_A)
		game->player.move.left = 1;
	if (keycode == KEY_D)
		game->player.move.right = 1;
	if (keycode == RIGHT)
		game->player.rotate.right = 1;
	if (keycode == LEFT)
		game->player.rotate.left = 1;
	// //printf("auch%d\n ", keycode); //borrarmove_front
	return (0);
}

int	ft_key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->player.move.front = 0;
	if (keycode == KEY_S)
		game->player.move.back = 0;
	if (keycode == KEY_A)
		game->player.move.left = 0;
	if (keycode == KEY_D)
		game->player.move.right = 0;
	if (keycode == LEFT)
		game->player.rotate.left = 0;
	if (keycode == RIGHT)
		game->player.rotate.right = 0;
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

	if (map.matrix[(int)new_pos.y][(int)player->current_pos.x] == '0') // Aca se revisa si el movimiento se sale del mapa 
		player->current_pos.y = new_pos.y;
	if (map.matrix[(int)player->current_pos.y][(int)new_pos.x] == '0') // si queremos el norte en el norte y es la primera posicion
		player->current_pos.x = new_pos.x;
}

//move backwards if no wall behind you
void			ft_move_back(t_map map, t_player *player)
{
	t_position	new_pos;

	new_pos.x = player->current_pos.x - player->orientation.x * MOVE_SPEED;
	new_pos.y = player->current_pos.y - player->orientation.y * MOVE_SPEED;
	if (map.matrix[(int)new_pos.y][(int)player->current_pos.x] == '0')
		player->current_pos.y = new_pos.y;
	if (map.matrix[(int)player->current_pos.y][(int)new_pos.x] == '0')
		player->current_pos.x = new_pos.x;
}

void			ft_move_right(t_map map, t_player *player)
{
	t_position	new_pos;
	new_pos.x = player->current_pos.x + player->plane.x * MOVE_SPEED;
	new_pos.y = player->current_pos.y + player->plane.y * MOVE_SPEED;
	if (map.matrix[(int)new_pos.y][(int)player->current_pos.x] == '0')
		player->current_pos.y = new_pos.y;
	if (map.matrix[(int)player->current_pos.y][(int)new_pos.x] == '0')
		player->current_pos.x = new_pos.x;
}

void			ft_move_left(t_map map, t_player *player)// tarea factorizar
{
	t_position	new_pos;
	new_pos.x = player->current_pos.x - player->plane.x * MOVE_SPEED;
	new_pos.y = player->current_pos.y - player->plane.y * MOVE_SPEED;
	if (map.matrix[(int)new_pos.y][(int)player->current_pos.x] == '0')
		player->current_pos.y = new_pos.y;
	if (map.matrix[(int)player->current_pos.y][(int)new_pos.x] == '0')
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
	if (player->move.front == 1)
		ft_move_front(map, player);
	if (player->move.back == 1)
		ft_move_back(map, player);
	if (player->move.left == 1)
		ft_move_left(map, player);
	if (player->move.right == 1)
		ft_move_right(map, player);
	if (player->rotate.left == 1)
		ft_turn_left(player);
	if (player->rotate.right == 1)
		ft_turn_right(player);
	return (0);
}

t_texture		ft_get_textures(t_screen screen, t_ray *ray)
{
	t_texture	texture;
	if (ray->side == 0)
	{
		if (ray->dir.x < 0){
		////printf("choosed texture West address %p.width %d, texture height %d, bpp %d , size %d \n"  ,screen.west.address, screen.west.width, screen.west.height, screen.west.bits_per_pixel, screen.west.size_line);
			texture = screen.west;
		}
		else{
		////printf("choosed  texture Est address %p. width %d, texture height %d, bpp %d , size %d \n"  ,screen.east.address, screen.east.width, screen.east.height, screen.east.bits_per_pixel, screen.east.size_line);
			texture = screen.east;
		}
	}
	else
	{
		if (ray->dir.y < 0){
	////printf("choosed texture North address %p. width %d, texture height %d, bpp %d , size %d \n" ,screen.north.address, screen.north.width, screen.north.height, screen.north.bits_per_pixel, screen.north.size_line);
			texture = screen.north;
		}
		else{
	////printf("choosed texture south address %p. width %d, texture height %d, bpp %d , size %d \n"  ,screen.south.address, screen.south.width, screen.south.height, screen.south.bits_per_pixel, screen.south.size_line);
			texture = screen.south;
		}
	}
	return(texture);
}

int			ft_get_color(t_texture texture, t_wall wall)
{
	int		color;
	char	*dst;

	dst = texture.address + ((int)wall.pos.y * texture.size_line +
		((int)wall.pos.x * (texture.bits_per_pixel / EIGHT_BITS)));
	color = *(unsigned int*)dst;
	return (color);
}

void		ft_put_pixel(t_texture *texture, int x, int y, int color)
{
	char	*dst;
	////printf("address %p y %d size %d  bits_per_pixel %d\n", texture->address, y, texture-> size_line, texture->bits_per_pixel);
	dst = texture->address + (y * texture->size_line +
		x * (texture->bits_per_pixel / EIGHT_BITS));
	*(unsigned int*)dst = color;
}

/*
** - texture->step_size = How much to increase the texture coordinate
**	 per screen pixel.
** - texture->start_pos = Starting texture coordinate.
**
*/

void	ft_draw_walls(t_ray *ray, t_screen *screen, int x)// name of function render wall??
{
	int y;
	int color;
	t_texture texture;

	screen->wall.step = 1.0 * TEXTURE_HEIGHT / ray->line_height;
	screen->wall.start_pos = (ray->draw_start - screen->win_size.height / 2 +
		ray->line_height / 2) * screen->wall.step;
	y = ray->draw_start;

	//printf("draw_start:%d ray->draw_end:%d, X:%d\n", ray->draw_start,ray->draw_end, x);
	while (y < ray->draw_end)
	{
		screen->wall.pos.y = (int)screen->wall.start_pos & (TEXTURE_HEIGHT - 1);
		screen->wall.start_pos += screen->wall.step;
		texture = ft_get_textures(*screen, ray);
		color = ft_get_color(texture, screen->wall);
		if (ray->side == 1)
			color = (color >> 1) & DARKER;//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		ft_put_pixel(&screen->win_data, x, y, color);
		y++;
	}
}

/*
** Draw the pixels of the stripe as a vertical line.
** - ray->wall_x = where exactly the wall was hit. This is required to know
** 	 which x-coordinate of the texture we have to use.
** - wall->pos.x = is the x-coordinate of the texture, and this is calculated
**	out of wall_x.
*/

//calculate value of wallX

void	ft_calc_wall_pos(t_ray *ray, t_wall *wall, t_position current)
{
	if (ray->side == 0)
		ray->wall_x = current.y + ray->perpwalldist * ray->dir.y;
	else
		ray->wall_x = current.x + ray->perpwalldist * ray->dir.x;
	ray->wall_x -= floor(ray->wall_x);
	wall->pos.x = (int)(ray->wall_x * (double)TEXTURE_WIDTH);
	if ((ray->side == 0 && ray->dir.x > 0)
		|| (ray->side == 1 && ray->dir.y < 0))
		wall->pos.x = TEXTURE_WIDTH - wall->pos.x - 1;
}

/*
** Calculate height of line to draw on screen the raycasting.
** Calculate lowest and highest pixel to fill in current stripe.
*/

void	ft_calc_draw_limits(t_ray *ray, t_win_size win_size)
{
	ray->line_height = (int)(win_size.height / ray->perpwalldist);
	ray->draw_start = -ray->line_height / 2 + win_size.height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->line_height / 2) + (win_size.height / 2);
	if (ray->draw_end >= win_size.height)
		ray->draw_end = win_size.height - 1;
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

void	ft_calc_wall_dist(t_ray *ray, t_position current)
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
** map.matrix[y][x] in this order of x and y, North face up
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
		//printf("checking map  %d %d %c\n", x , y , map.matrix[x][y]);//borrar

		if (map.matrix[y][x] == '1') {
		/// revisar esta linea //(game->map.matrix[ray->map_x][ray->map_y] == '1') /// esto es el muro. porque es 1
		// //printf("jugo\n");
			hit = 1;
		}
	}
}
// Now, before the actual DDA can start, first stepX, stepY,
// and the initial sideDistX and sideDistY still have to be calculated.

void			ft_calc_side_dist(t_position current, t_ray *ray)
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

	ray = &game->player.ray;
	// //printf("loading player  %f %f\n", game->player.direction.x  ,game->player.direction.y);
	ray->camera_x = 2 * x / (double)game->screen.win_size.width - 1;
	
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

	//printf("resoultion W%d, H%d\n", game->screen.resolution.width, game->screen.resolution.height); //borrar
	x = 0;
	while (x < game->screen.win_size.width)
	{
		ft_set_ray_position(game, x);
		ft_calc_side_dist(game->player.current_pos, &game->player.ray);
		ft_perform_dda(game->map, &game->player.ray);
		ft_calc_wall_dist(&game->player.ray, game->player.current_pos);
		ft_calc_draw_limits(&game->player.ray, game->screen.win_size);
		ft_calc_wall_pos(&game->player.ray, &game->screen.wall, game->player.current_pos); // REVISAR SI CAMBIA CONSTANTE POR TEXTURA
		ft_draw_walls(&game->player.ray, &game->screen, x);
		ft_draw_floor_ceiling(&game->screen, game->player.ray, x);
		x++;
	}
	mlx_put_image_to_window(game->screen.mlx, game->screen.window,
		game->screen.win_data.image, 0, 0);
	//timing for input and FPS counter
	//printf("Poniendo imagen %p %d\n",game->screen.win_data.address, game->screen.win_data.size_line ); //borrar
}

int			ft_set_orientation(t_map map, t_player *player)
{
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

int			ft_set_all_textures(t_game_file file, t_screen *screen)
{
	int		result;

	result = ft_set_texture(screen->mlx, file.no_path, &screen->north)
	&& ft_set_texture(screen->mlx, file.so_path, &screen->south)
	&& ft_set_texture(screen->mlx, file.we_path, &screen->west)
	&& ft_set_texture(screen->mlx, file.ea_path, &screen->east)
	&& ft_set_texture(screen->mlx, file.sprite_path, &screen->sprite);
	
	return (result);
}

// aqui podria incluirse destroy window cuando screenshot no se necesita

/*
** Initializing the game screen
**
** @param t_game_file file: 	the input file (e.g. "file.cub" validated)
** @param t_game *game: 		the game instance
**
** @return int:					1 is ok
*/

int				ft_set_screen(t_screen *screen)
{
	t_texture	*data;

	//printf("init resolution w:%d h:%d\n", screen->resolution.width, screen->resolution.height); //borrar
	data = &screen->win_data;
	screen->mlx = mlx_init();
	if (screen->mlx == NULL)
		return (ft_put_error("mlx connection failure"));
	screen->window = mlx_new_window(screen->mlx,
		screen->win_size.width, screen->win_size.height, "Welcome");
	if (screen->window == NULL)
		return (ft_put_error("mlx window failure"));
	data->image = mlx_new_image(screen->mlx,
		screen->win_size.width, screen->win_size.height);
	if (data->image == NULL)
		return (ft_put_error("mlx image failure"));
	data->address = mlx_get_data_addr(data->image, &data->bits_per_pixel,
		&data->size_line, &data->endian);
	if (data->address == NULL)
		return (ft_put_error("mlx address image failure"));
	return (1);
}

int	ft_is_moving(t_movements move, t_rotations rotate)
{
	return (move.front || move.back || move.left
		|| move.right || rotate.right || rotate.left);
}

int	ft_play_game(t_game *game)
{
	if (ft_is_moving(game->player.move, game->player.rotate))
	{
		ft_manage_movements(game->map, &game->player);
		ft_render_map(game);
		// printf("posicion %f %f\n", game->player.current_pos.x, game->player.current_pos.y);
		// printf("plano %f %f\n", game->player.plane.x, game->player.plane.y);
	}
	return (0);
}

int ft_set_game(t_game_file file, t_game *game)
{
	game->map = file.map;
	game->screen.win_size = file.win_size;

	ft_clean_game(&game->screen, &game->player);
	if (!ft_set_screen(&game->screen))
		ft_put_error("set screen failure"); // ok
	ft_set_floor_ceiling(file, &game->screen);//ok
	ft_set_all_textures(file, &game->screen); //ok
	ft_set_orientation(game->map, &game->player);
	ft_render_map(game);
	return(1);
}

int			ft_start_game(t_game_file file)
{
	t_game	game;

	ft_set_game(file, &game);
	mlx_hook(game.screen.window, DESTROY, NOTIFY_MASK, &ft_close_game, &game);
	mlx_hook(game.screen.window, PRESS, PRESS_MASK, &ft_key_press, &game);
	mlx_hook(game.screen.window, RELEASE, RELEASE_MASK, &ft_key_release, &game);
	mlx_loop_hook(game.screen.mlx, &ft_play_game, &game);
	mlx_loop(game.screen.mlx);
	return (0);
}
