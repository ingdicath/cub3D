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
/*
** ---------- Movements ----------
*/
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define ESC 53
# define LEFT 123
# define RIGHT 124
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

typedef struct	s_input
{
	char		*no_texture;
	char		*so_texture;
	char		*ea_texture;
	char		*we_texture;
	char		*sprite;
	int			screenshot;
	t_color		ceiling;
	t_color		floor;
	t_screen	resolution;
	t_map		map;
}				t_input;

/*
** ---------- Raycasting structures ---------------
*/

typedef struct  s_mlx
{
	void		*mlx;
	void		*window; 
	void		*image;
	char		*address;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int 		width_texture;
	int 		heigth_texture;
}				t_mlx;

typedef struct s_texture
{
	void		*texture;
	void		*window; 
	char		*address;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int 		width_texture;
	int 		heigth_texture;
}				t_texture;

typedef struct s_game
{
	double		start_posx;
	double		start_posy;
	double		vector_dirx;
	double		vector_diry;
	double		plane_x;
	double		plane_y;
	double		time;
	double		old_time;
}				t_game;

typedef struct s_moves   // o mejor llamarlo p
{
	int			move_up;
	int			move_down;
	int			move_right;
	int			move_left;
	int			rotate_right;
	int			rotate_left;
}				t_moves;

typedef struct s_create
{
	t_mlx		mlx;
	t_game		game;
	t_screen	screen;
}			t_create;
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

void			ft_reset_input(t_input *mapfile);
int				ft_read_file_map(char *file_name, t_input *mapfile);
int				ft_check_valid_color(char *color);
int				ft_check_resolution(char **line, t_screen *resolution);
int				ft_check_ceiling(char **line, t_color *ceiling);
int				ft_check_floor(char **line, t_color *floor);
int				ft_check_north_texture(char **line, char **north_path);
int				ft_check_west_texture(char **line, char **west_path);
int				ft_check_east_texture(char **line, char **east_path);
int				ft_check_south_texture(char **line, char **south_path);
int				ft_check_sprite_texture(char **line, char **sprite_path);
int				ft_check_complete_elements(t_input *mapfile);
int				ft_array_size(char **array);
int				ft_check_path(char *str);
int				ft_check_extension(char *file_name, char *valid_ext);
int				ft_check_valid_char(char *line);
int				ft_fill_elements(char **line_split, t_input *mapfile);
char			**ft_join_lines(char **matrix, char *new_line);
int				ft_check_unique_orientation(t_map *map);
// int				ft_check_args(argc, argv);

void			printfs(t_input *mapfile);//BORRAR
void			print_map(char **map);//BORRAR

#endif
