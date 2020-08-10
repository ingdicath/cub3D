/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 11:20:00 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/10 13:52:39 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
** ----------- Extensions -----------------------------------------------------
*/

# define CUB 	".cub"
# define XPM 	".xpm"
# define PNG 	".png"
# define BMP 	".bmp"

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
	double		row;
	double		column;
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
	int			width; // validar
	int			height; // validar
}				t_texture;

typedef struct	s_board
{
	void		*mlx;
	void		*window;
	t_texture	win_data;
	t_texture	north;
	t_texture	south;
	t_texture	west;
	t_texture	east;
	t_texture	sprite;
	// void		*image;
	// char		*address;
	// int			bits_per_pixel;
	// int			line_length;
	// int			endian;
}				t_board;

typedef struct	s_player
{
	double		direction_x;
	double		direction_y;
	double		plane_x;
	double		plane_y;
	double		time;
	double		old_time;
}				t_player;

typedef struct	s_movements
{
	int			move_front;
	int			move_back;
	int			move_right;
	int			move_left;
	int			rotate_right;
	int			rotate_left;
}				t_movements;

typedef struct	s_ray
{
	double		camera_x;
	double		dir_x;
	double		dir_y;
	double		deltadist_x;
	double		deltadist_y;
	double		sidedist_x;
	double		sidedist_y;
	int			step_x;
	int			step_y;
	int			map_x;
	int			map_y;
}				t_ray;

typedef struct	s_game // Game
{
	t_board		board;
	t_player	player;
	t_map		map;
	// t_screen	screen;
}				t_game;

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
size_t			ft_count_words(char const *s, char c);
void			ft_putstr(char *str);
void			ft_putchar(char c);
int				ft_atoi(const char *str);
int				ft_isnumber(char *str);

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

/*
** ---------- Raycasting functions --------------------------------------------
*/

int				ft_close_game(t_game *game);
int				ft_play_game(int keycode, t_game *game, t_map map);
int				ft_key_press(int keycode, t_game *game);
int				ft_key_release(int keycode, t_game *game);
int				ft_start_game(t_game_file game_file);
int				ft_save_screen (t_game_file game_file);
int				ft_set_board(t_game_file file, t_game *game);
int				ft_set_all_textures(t_game_file file, t_board *board);
int				ft_set_texture(void *mlx, char *path, t_texture *texture);
void			ft_initialize_player(t_player *player);
int				ft_set_orientation(char orientation, t_player *player);
int				ft_render_map(t_game *game, t_screen resolution);
void			ft_set_initial_step_sidedist(t_game *game, t_ray *ray);
void			ft_perform_dda(t_game *game, t_ray *ray);

/*
** ---------- DELETEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE ---------------
*/

void			printfs(t_game_file *mapfile);//BORRAR
void			print_map(char **map);//BORRAR

#endif
