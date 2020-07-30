/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 11:20:00 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/07/29 11:37:18 by dsalaman      ########   odam.nl         */
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
	char		**map;
	int			start_pos_x;
	int			start_pos_y;
}				t_input;

/*
** Verificar como trabajar el mapa
*/

typedef struct	s_map
{
	char		**map_array;
	int			map_width;
	int			map_height;
}				t_map;

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
int				ft_istab(char c);

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
int				ft_fill_map(char *line, t_input *mapfile);
char			*ft_join_lines(char *line, char *new_line);//REVISAR

void			printfs(t_input *mapfile);//BORRAR
void			print_map(char **map);//BORRAR

#endif
