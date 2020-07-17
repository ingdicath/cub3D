#ifndef CUB3D_H
# define CUB3D_H
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include "mlx/mlx.h"

# define SCREENSHOT --save



// typedef         s_input
// {
//     char        *no_texture;
//     char        *so_texture;
//     char        *ea_texture;
//     char        *we_texture;
//     char        *sprite;
//     t_color     ceiling;
//     t_color     floor;
//     t_screen    resolution;
//     char        **map;
// }               t_input;

// typedef         s_color
// {
//     int         red;
//     int         green;
//     int         blue;
// }               t_color;

// typedef         s_screen
// {
//     int         width;
//     int         height;
// }               t_screen;


// /* Verificar como trabajar el mapa */

// typedef         s_map
// {
//     char        **map_array;
//     int         map_width;
//     int         map_height;
//     int         pos_x;
//     int         pos_y;
//     char        *file_ext; //verificar como incluir la ext aqui
// }               t_map;

void	        ft_putstr_fd(char *s, int fd);
int             ft_put_error(char *error);
// size_t		    ft_strlen(const char *s);
int         ft_strlen(char const *s);
int		        ft_strncmp(const char *s1, const char *s2, size_t n);
char		    *ft_substr(char *s, unsigned int start, size_t len);
char		    *ft_strdup(const char *s1);
char		    *ft_strchr(const char *s, int c);
char		    *ft_strjoin(char *s1, char *s2);
int             ft_check_file_type(char *map_ext);
int             ft_iswhitespace(char c);
char            **ft_split(char *s, char c);
size_t  ft_count_words(char const *s, char c);


#endif