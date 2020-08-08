/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 11:20:00 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/07 17:01:16 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
/*
** ---------- Extensions ----------
*/
# define CUB 	".cub"
# define XPM 	".xpm"
# define PNG 	".png"
# define BMP 	".bmp"
/*
** ---------- Movements ----------
*/
// *****************************************CAMBIAR A ENUuuuuuuuuuMS
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define ESC 53
# define LEFT 123
# define RIGHT 124
/*
** ---------- Events ----------
*/
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define DESTROY_NOTIFY 17

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include "mlx/mlx.h"
# include "gnl/get_next_line.h"

/*
** ---------- Parsing structures ---------------
*/

typedef enum e_masks
{
	PRESS_MASK = 1, RELEASE_MASK = 2, NOTIFY_MASK = 3
}			t_masks;

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

typedef struct 	s_pos
{
	int 		row;
	int 		column;
}				t_pos;

typedef struct	s_map
{
	char		**data;
	char		orientation;
	t_pos		start_pos;
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
** ---------- Raycasting structures ---------------
*/

typedef struct  s_board // Maze // Window // Board
{
	void		*mlx;
	void		*window; 
	void		*image;
	char		*address;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int 		width_texture; // validar
	int 		heigth_texture; // validar
}				t_board;

// typedef struct s_texture //validar
// {
// 	void		*texture;
// 	void		*window; 
// 	char		*address;
// 	int			bits_per_pixel;
// 	int			line_length;
// 	int			endian;
// 	int 		width_texture; // validar
// 	int 		heigth_texture; // validar
// }				t_texture;

typedef struct s_player     // player
{
	double		start_posx;
	double		start_posy;
	double		vector_dirx;
	double		vector_diry;
	double		plane_x;
	double		plane_y;
	double		time;
	double		old_time;
}				t_player;

typedef struct s_movements   // o mejor llamarlo acciones // movements
{
	int			move_up;
	int			move_down;
	int			move_right;
	int			move_left;
	int			rotate_right;
	int			rotate_left;
}				t_movements;

typedef struct s_game // Game
{
	t_board		board;
	t_player	player;
	t_screen	screen;	
}			t_game;
/*
** ---------- Auxiliary functions ----------
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
** ---------- Parsing functions ---------------
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
int 			ft_check_args(int argc, char **argv, int *screenshot);

/*
** ---------- Raycasting functions ---------------
*/

int ft_close_game(t_game *game);
int ft_movements(int keycode, t_game *game);
int ft_key_press(int keycode, t_game *game);
int ft_key_release(int keycode, t_game *game);
int ft_start_game(t_game_file game_file);
int ft_save_screen (t_game_file game_file);
int ft_set_board(t_game_file file, t_game *game);

void			printfs(t_game_file *mapfile);//BORRAR
void			print_map(char **map);//BORRAR

#endif
