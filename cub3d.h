/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/17 15:45:04 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/07/20 21:27:02 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include "mlx/mlx.h"
# include "gnl/get_next_line.h"

typedef struct         s_color
{
    int         red;
    int         green;
    int         blue;
}               t_color;

typedef struct         s_screen
{
    int         width;
    int         height;
}               t_screen;


typedef struct  s_input
{
    char        *no_texture;
    char        *so_texture;
    char        *ea_texture;
    char        *we_texture;
    char        *sprite;
    t_color     ceiling;
    t_color     floor;
    t_screen    resolution;
    char        **map;
}               t_input;



/* Verificar como trabajar el mapa */

typedef struct         s_map
{
    char        **map_array;
    int         map_width;
    int         map_height;
    int         pos_x;
    int         pos_y;
    char        *file_ext; //verificar como incluir la ext aqui
}               t_map;




void	        ft_putstr_fd(char *s, int fd);
int             ft_put_error(char *error);
// size_t		    ft_strlen(const char *s);
int             ft_strlen(char const *s);
int		        ft_strncmp(const char *s1, const char *s2, size_t n);
char		    *ft_substr(char *s, unsigned int start, size_t len);
char		    *ft_strdup(const char *s1);
char		    *ft_strchr(const char *s, int c);
char		    *ft_strjoin(char *s1, char *s2);
int             ft_check_file_type(char *map_name);
int             ft_iswhitespace(char c);
char            **ft_split(char *s, char c);
size_t          ft_count_words(char const *s, char c);
void            ft_putstr(char *str);
void            ft_putchar(char c);
int 			ft_read_file_map(char *file_name, t_input *mapfile);
int 			ft_check_resolution(char **line, t_screen *resolution);
int				ft_atoi(const char *str);
int 			ft_check_ceiling(char **line, t_color *ceiling);
int 			ft_check_floor(char **line, t_color *floor);
int				ft_isnumber(char *str);
int 			ft_check_valid_color(char *color);
int             ft_check_north_texture(char **line, char *north_path);
int             ft_check_west_texture(char **line, char *west_path);
int             ft_check_east_texture(char **line, char *east_path);
int             ft_check_texture_so_sprite(char **line, char *texture);
int             ft_check_unique_type(t_input *mapfile);

#endif