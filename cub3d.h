#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include "mlx/mlx.h"

typedef     s_input
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
}           t_input;

typedef     s_color
{
    int     red;
    int     green;
    int     blue;
}           t_color;

typedef     s_screen
{
    int     width;
    int     height;
}           t_screen;



#endif