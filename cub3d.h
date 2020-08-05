/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 11:20:00 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/07/31 15:20:57 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
** ---------- Extensions ----------
*/
# define CUB ".cub"
# define XPM ".xpm"
# define PNG ".png"
# define ESC 53
# define LEFT 123
# define RIGHT 124
# define UP 126
# define DOWN 125
# define W_UP 13
# define A_LEFT 0
# define S_DOWN 1
# define D_RIGHT 2

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include "mlx/mlx.h"
# include "gnl/get_next_line.h"

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
	t_color		ceiling;
	t_color		floor;
	t_screen	resolution;
	t_map		map;
}				t_input;



/*
** Verificar como trabajar el mapa
*/




typedef struct s_ray
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		time;
	double		oldTime;
}				t_ray;
/*
** Verificar como trabajar el mapa
*/



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

void			printfs(t_input *mapfile);//BORRAR
void			print_map(char **map);//BORRAR

#endif
