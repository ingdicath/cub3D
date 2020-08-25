/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 11:20:00 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/25 17:00:26 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
** ----------- Extensions & BMP name file -------------------------------------
*/

# define CUB ".cub"
# define XPM ".xpm"
# define PNG ".png"
# define SCREENSHOT "cub3d_screenshot.bmp"

/*
** ----------- Speed & moves --------------------------------------------------
*/

# define ROTATE_SPEED 0.03
# define MOVE_SPEED 0.07

/*
** ----------- Colors ---------------------------------------------------------
** To build rgb format system: red in the bit 16 =  1 << 16;
** green in the bit 8 =  1 << 8, blue is in the bit 1.
*/

# define RED_BIT 65536
# define GREEN_BIT 256
# define DARKER 7566197

/*
** ----------- Libraries ------------------------------------------------------
*/

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "mlx/mlx.h"
# include "libft/libft.h"
# include <stdio.h> // BORRAR

/*
** ----------- Actions constants ----------------------------------------------
*/

typedef enum	e_keys
{
	KEY_A = 0, KEY_S = 1, KEY_D = 2, KEY_W = 13, ESC = 53, LEFT = 123,
	RIGHT = 124
}				t_keys;

typedef enum	e_events
{
	PRESS = 2, RELEASE = 3, DESTROY = 17
}				t_events;

typedef enum	e_masks
{
	PRESS_MASK = 1, RELEASE_MASK = 2, NOTIFY_MASK = 3
}				t_masks;

/*
** ----------- Sprites constants ----------------------------------------------
*/

typedef enum	e_sp_constants
{
	V_MOVE = 0, U_DIV = 1, V_DIV = 1
}				t_sp_constants;

/*
** ----------- Util constants -------------------------------------------------
*/

typedef enum	e_sizes
{
	TEXTURE_WIDTH = 64, TEXTURE_HEIGHT = 64, ONE_BYTE = 1, TWO_BYTES = 2,
	FOUR_BYTES = 4, EIGHT_BITS = 8
}				t_sizes;

typedef enum	e_bmp
{
	RESERVED_1 = 2, RESERVED_2 = 2, FILE_HEADER = 14, INFO_HEADER = 40,
	PLANE = 1, FINAL_IMAGE_SIZE = 54, BITS_PER_PIXEL = 32,
	BMP_PIXELS = 24, COMPRESSION = 4, IMAGE_SIZE = 4, X_PPM = 4, Y_PPM = 4,
	TOTAL_COLORS = 4, IMPORTANT_COLORS = 4
}				t_bmp;

/*
** ----------- Parsing structures ----------------------------------------------
*/

typedef struct	s_color
{
	int			red;
	int			green;
	int			blue;
}				t_color;

typedef struct	s_size
{
	int			width;
	int			height;
}				t_size;

typedef struct	s_position
{
	double		x;
	double		y;
}				t_position;

typedef struct	s_sprite
{
	double		distance;
	t_position	position;
}				t_sprite;

typedef struct	s_map
{
	char		**matrix;
	double		*zbuffer;
	int			num_sprites;
	char		orientation;
	t_sprite	*sprites;
	t_position	start_pos;
}				t_map;

typedef struct	s_game_file
{
	char		*no_path;
	char		*so_path;
	char		*ea_path;
	char		*we_path;
	char		*sprite_path;
	t_color		ceiling;
	t_color		floor;
	t_size		resolution;
	t_map		map;
}				t_game_file;

/*
** ----------- Raycasting structures ------------------------------------------
*/

typedef struct	s_texture
{
	void		*image;
	char		*address;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			width;
	int			height;
}				t_texture;

typedef struct	s_wall
{
	double		step;
	double		start_pos;
	t_position	pos;
}				t_wall;

typedef struct	s_ray
{
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			side;
	double		perpwalldist;
	double		camera_x;
	double		wall_x;
	t_position	dir;
	t_position	deltadist;
	t_position	sidedist;
	t_position	step;
	t_position	map;
}				t_ray;

typedef struct	s_sprite_cast
{
	int			screen_x;
	t_size		size;
	t_position	transform;
	t_position	draw_start;
	t_position	draw_end;
}				t_sprite_cast;

typedef struct	s_screen
{
	void		*mlx;
	void		*window;
	int			ceiling;
	int			floor;
	t_wall		wall;
	t_size		resolution;
	t_size		max_res;
	t_texture	win_data;
	t_texture	north;
	t_texture	south;
	t_texture	west;
	t_texture	east;
	t_texture	sprite;
}				t_screen;

typedef struct	s_movements
{
	int			front;
	int			back;
	int			right;
	int			left;
}				t_movements;

typedef struct	s_rotations
{
	int			left;
	int			right;
}				t_rotations;

typedef struct	s_player
{
	t_position	orientation;
	t_position	plane;
	t_position	current_pos;
	t_movements	move;
	t_rotations rotate;
	t_ray		ray;
}				t_player;

typedef struct	s_game
{
	t_screen	screen;
	t_player	player;
	t_map		map;
}				t_game;

/*
** ----------- Parsing functions ----------------------------------------------
*/

void			ft_reset_input(t_game_file *mapfile);
int				ft_read_file(char *file_name, t_game_file *file);
int				ft_check_valid_color(char *color);
int				ft_check_resolution(char **line, t_size *resolution);
int				ft_check_ceiling(char **line, t_color *ceiling);
int				ft_check_floor(char **line, t_color *floor);
int				ft_check_north_path(char **line, char **north_path);
int				ft_check_west_path(char **line, char **west_path);
int				ft_check_east_path(char **line, char **east_path);
int				ft_check_south_path(char **line, char **south_path);
int				ft_check_sprite_path(char **line, char **sprite_path);
int				ft_check_complete_elements(t_game_file *mapfile);
int				ft_array_size(char **array);
int				ft_check_path(char *str);
int				ft_check_extension(char *file_name, char *valid_ext);
int				ft_check_valid_char(char c);
int				ft_fill_elements(char **line_split, t_game_file *mapfile);
char			**ft_join_lines(char **matrix, char *new_line);
int				ft_check_unique_orientation(t_map *map, int i, int j);
int				ft_check_args(int argc, char **argv, int *screenshot);
int				ft_count_sprites(char *line, t_map *map);
int				ft_set_sprites_and_orientation(t_map *map);
int				ft_check_map(t_map map);
int				ft_flood_fill(char **matrix, int x, int y);
int				ft_uncovered_map(char **matrix);
int 			ft_read_line(t_game_file *file, char *line);
int 			ft_parsing(int argc, char **argv, t_game_file *file,
					int *screenshot);

/*
** ---------- Raycasting functions --------------------------------------------
*/

int				ft_close_game(t_game *game);
int				ft_play_game(t_game *game);
int				ft_key_press(int keycode, t_game *game);
int				ft_key_release(int keycode, t_game *game);
int				ft_set_game(t_game_file file, t_game *game, int screenshot);
int				ft_start_game(t_game_file game_file);
int				ft_set_screen(t_screen *screen, int screenshot);
int				ft_set_all_textures(t_game_file file, t_screen *screen);
int				ft_set_texture(void *mlx, char *path, t_texture *texture);
int				ft_set_orientation(t_map map, t_player *player);
void			ft_render_map(t_game *game);
void			ft_calc_side_dist(t_position current, t_ray *ray);
void			ft_perform_dda(t_map map, t_ray *ray);
void			ft_calc_wall_dist(t_ray *ray, t_position current);
void			ft_calc_draw_limits(t_ray *ray, t_size resolution);
void			ft_calc_wall_pos(t_ray *ray, t_wall *wall, t_position current);
void			ft_draw_walls(t_ray *ray, t_screen *screen, int x);
t_texture		ft_get_textures(t_screen screen, t_ray *ray);
void			ft_clean_game(t_screen *screen, t_player *player, t_map *map);
void			ft_put_pixel(t_texture *texture, int x, int y, int color);
int				ft_get_color(t_texture texture, t_position position);
void			ft_set_ray_position(t_game *game, int x);
void			ft_move_front(t_map map, t_player *player);
void			ft_move_back(t_map map, t_player *player);
void			ft_move_right(t_map map, t_player *player);
void			ft_move_left(t_map map, t_player *player);
void			ft_turn_right(t_player *player);
void			ft_turn_left(t_player *player);
int				ft_manage_movements(t_map map, t_player *player);
int				ft_rgb_calculator(int r, int g, int b);
void			ft_set_floor_ceiling(t_game_file file, t_screen *screen);
void			ft_draw_floor_ceiling(t_screen *screen, t_ray ray, int x);
void			ft_set_header_bitmap(int fd, t_screen *screen);
void			ft_put_pixel_bitmap(int fd, t_screen *screen);
void			ft_take_screenshot(t_game_file game_file);
int				ft_is_moving(t_movements move, t_rotations rotate);
void			ft_write_char_zeros(int fd, int times);
void			ft_write_short_bytes(int fd, int param);
void			ft_write_int_bytes(int fd, int param);
void			ft_inverse_camera(t_sprite sprite, t_sprite_cast *s_cast,
					t_player player, int w);
int				ft_render_sprites(t_game *game);
void			ft_calc_sprite_limits(t_sprite_cast *s_cast, t_size resolution);
void			ft_vertical_stripes(t_sprite_cast *s_cast, t_screen screen,
					double *zbuffer);
void			ft_draw_stripes(t_sprite_cast *s_cast, t_screen screen,
					t_position *tex, int stripe);
void			ft_sort_sprites(t_map *map, t_position current_pos);
void			ft_calc_dist_sprite (t_map *map, t_position current_pos);
int				ft_resize_resolution(t_screen *screen);
int				ft_calc_sprite_variables(t_map *map, int i, int j, int k);
int				ft_memory_space_sprites(t_map *map);

/*
** ---------- DELETEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE ---------------
*/

void			printfs(t_game_file *mapfile);//BORRAR
void			print_map(char **map);//BORRAR
void 			print_array(t_sprite *sprites, int x);

#endif
