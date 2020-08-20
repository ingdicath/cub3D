/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 11:20:00 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/20 16:50:31 by dsalaman      ########   odam.nl         */
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

# define ROTATE_SPEED 0.15
# define MOVE_SPEED 0.7

/*
** ----------- Colors ---------------------------------------------------------
** To build rgb format system: red in the bit 16 =  1 << 16;
** green in the bit 8 =  1 << 8, blue is in the bit 1.
*/

# define RED_BIT 65536
# define GREEN_BIT 256

/*
** ----------- Libraries ------------------------------------------------------
*/

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include "mlx/mlx.h"
# include "gnl/get_next_line.h"

/*
** ----------- Actions structures ---------------------------------------------
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
** ----------- Constants ------------------------------------------------------
*/

typedef enum	e_sizes
{
	TEXTURE_WIDTH = 64, TEXTURE_HEIGHT = 64, ONE_BYTE = 1, TWO_BYTES = 2,
	FOUR_BYTES = 4
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

typedef struct	s_screen
{
	int			width;
	int			height;
}				t_screen;

typedef struct	s_position
{
	double		x;
	double		y;
}				t_position;

typedef struct	s_map
{
	char		**data;
	char		orientation;
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
	t_screen	resolution;
	t_map		map;
}				t_game_file;

/*
** ----------- Raycasting structures ------------------------------------------
*/

typedef struct	s_texture //validar
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
	t_wall		tex;
}				t_ray;

typedef struct	s_board
{
	void		*mlx;
	void		*window;
	double		*buffer;  // Uint32 buffer[screenHeight][screenWidth], no se ha usado todavia
	int			ceiling;
	int			floor;
	int			screenshot;
	t_screen	resolution;
	t_texture	win_data;
	t_texture	north;
	t_texture	south;
	t_texture	west;
	t_texture	east;
	t_texture	sprite;
	t_ray		ray;
}				t_board;

typedef struct	s_movements
{
	int			move_front;
	int			move_back;
	int			move_right;
	int			move_left;
	int			turn_right;
	int			turn_left;
	// int 		close;   verificar si va dentro de esta estructura
}				t_movements;

typedef struct	s_player
{
	double		time;
	double		old_time;
	t_position	orientation;
	t_position	plane;
	t_position	current_pos;
	t_movements	move;
}				t_player;

typedef struct	s_game // Game
{
	int			screenshot;
	t_board		board;
	t_player	player;
	t_map		map;
}				t_game;

/*
** ----------- BMP ------------------------------------------------------------
*/

typedef struct		s_file_header
{
	char	*signature;
	unsigned int	size;
	unsigned int	reserved_1;
	unsigned int	reserved_2;
	unsigned int	pixel_data_offset;
}					t_file_header;

typedef struct		s_info_header
{
	unsigned int	dib_header_size;
	int				image_width;
	int				image_height;
	unsigned int	planes;
	unsigned int	bits_per_pixel;
	unsigned int	compression;
	unsigned int	image_size;
	int				x_pixels_per_meter;
	int				y_pixels_per_meter;
	unsigned int	num_colors;
	unsigned int	important_colors;
}					t_info_header;

typedef struct	s_bitmap
{
	t_file_header	file_header;
	t_info_header	info_header;

}				t_bitmap;



/*
** ----------- Auxiliary functions --------------------------------------------
*/

void			ft_putstr_fd(char *str, int fd);
int				ft_put_error(char *error);
size_t			ft_strlen(const char *s);
char			*ft_substr(char *s, unsigned int start, size_t len);
char			*ft_strdup(const char *s1);
char			*ft_strchr(const char *s, int c);
char			*ft_strjoin(char *s1, char *s2);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strcpy(char *dst, char const *src);
int				ft_isemptyline(char *str);
int				ft_iswhitespace(char c);
char			**ft_split(char *s, char c);
void			ft_putstr(char *str);
void			ft_putchar(char c);
int				ft_atoi(const char *str);
int				ft_isnumber(char *str);
void			ft_bzero(void *s, size_t n);

/*
** ----------- Parsing functions ----------------------------------------------
*/

void			ft_reset_input(t_game_file *mapfile);
int				ft_read_file(char *file_name, t_game_file *mapfile);
int				ft_check_valid_color(char *color);
int				ft_check_resolution(char **line, t_screen *resolution);
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
int				ft_check_valid_char(char *line);
int				ft_fill_elements(char **line_split, t_game_file *mapfile);
char			**ft_join_lines(char **matrix, char *new_line);
int				ft_check_unique_orientation(t_map *map);
int				ft_check_args(int argc, char **argv, int *screenshot);
// int			ft_check_args(int argc, char **argv, t_game *game);

/*
** ---------- Raycasting functions --------------------------------------------
*/

int				ft_close_game(t_game *game);
int				ft_play_game(t_game *game);
int				ft_key_press(int keycode, t_game *game);
int				ft_key_release(int keycode, t_game *game);
int ft_initialize(t_game_file file, t_game	*game);
int				ft_start_game(t_game_file game_file);
int				ft_set_board(t_board *board);
int				ft_set_all_textures(t_game_file file, t_board *board);
int				ft_set_texture(void *mlx, char *path, t_texture *texture);
void			ft_reset_player(t_player *player);
int				ft_set_orientation(t_map map, t_player *player);
void			ft_render_map(t_game *game);
void			ft_step_side_dist_init(t_position current, t_ray *ray);
void			ft_perform_dda(t_map map, t_ray *ray);
void			ft_perp_wall_dist(t_ray *ray, t_position current);
void			ft_screen_line_pixels_stripe(t_ray *ray, t_screen resolution);
void			ft_wall_texture(t_ray *ray, t_position current);
void			ft_texture_color(t_ray *ray, t_board board, int x);
t_texture		ft_get_textures(t_board board, t_ray *ray);
void			ft_reset_variables_game(t_board *board, t_player *player);
void			ft_put_pixel(t_texture *texture, int x, int y, int color);
int				ft_get_color(t_texture texture, t_ray ray);
void			ft_set_ray_position(t_game *game, int x);
void			ft_move_front(t_map map, t_player *player);
void			ft_move_back(t_map map, t_player *player);
void			ft_move_right(t_map map, t_player *player);
void			ft_move_left(t_map map, t_player *player);
void			ft_turn_right(t_player *player);
void			ft_turn_left(t_player *player);
int				ft_manage_movements(t_map map, t_player *player);
int				ft_rgb_calculator(int r, int g, int b);
void			ft_set_floor_ceiling_color(t_game_file file, t_board *board);
void			ft_draw_floor_ceiling_color(t_board *board, int x);
void	ft_set_header_bitmap(int fd, t_board *board);
void	ft_put_pixel_bitmap(int fd, t_board *board);
void	ft_take_screenshot(t_game_file game_file);


/*
** ---------- DELETEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE ---------------
*/

void			printfs(t_game_file *mapfile);//BORRAR
void			print_map(char **map);//BORRAR

#endif
