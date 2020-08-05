#include <mlx.h>


/* DRAWING A FIGURE*/

/*
typedef struct  s_data
{
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int main (void)
{
    void *mlx;
    void *mlx_win;
    t_data img;

    int i = 100;
    int j = 100;
    
    int x = 0;
    int y = 0;
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 800, 600, "Hello Pajarito");
    img.img = mlx_new_image(mlx, 800, 600);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    while (x <= i)
    {
        my_mlx_pixel_put(&img, x, y, 0x00FF0000);
        y = 0;
        while (y <= j)
        {
            my_mlx_pixel_put(&img, x, y, 0x00808080);
            y++;
        }
        x++;
    }
    mlx_put_image_to_window(mlx, mlx_win, img.img, 350, 250);
    mlx_loop(mlx);
}

*/

/* ---------------------------------------------------------------------------- */


/* HOOK - no funciona 
Esto se supone es para cerrar una ventana cuando se presiona una tecla */ 

/*

typedef struct s_vars
{
    void        *mlx;
    void        *win;
}               t_vars;

int close(int keycode, t_vars *vars)
{
    keycode = 0;
    mlx_destroy_window(vars->mlx, vars->win);
    return (0);
}

int main (void)
{
    t_vars  vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 800, 600, "Buenas");
    mlx_key_hook(vars.win, close, &vars);
    mlx_loop(vars.mlx);
}
*/

/* ---------------------------------------------------------------------------- */

/* HOOKING INTO EVENTS - using mlx_hook no funciona . 
Esto se supone es para cerrar una ventana cuando se presiona una tecla */ 


typedef struct s_vars
{
	void		*mlx;
	void		*win;
}               t_vars;

int close(int keycode, t_vars *vars)
{
    // keycode = 0;
    if (keycode == 53)
        mlx_destroy_window(vars->mlx, vars->win);
    return (0);
}

int main (void)
{
    t_vars  vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 800, 600, "Buenas");
    mlx_hook(vars.win, 2, 1L<<0, close, &vars);
    mlx_loop(vars.mlx);
}


/* ---------------------------------------------------------------------------- */

/* READING IMAGES - no probado
Toca tener una estructura para poder probarlo*/ 

/*
int render_next_frame (void *t_map)

int main (void)
{
    void *mlx;

    mlx = mlx_init();
    mlx_loop_hook(mlx, render_next_frame, t_map);
    mlx_loop(mlx);
}
*/

/* ---------------------------------------------------------------------------- */


/* READING AN IMAGE */ 

// Put xpm and png at the same time
/*
int main (void)
{
	void		*mlx;
	void		*img0;
    void        *img;
	void 		*mlx_win;
	char		*path0 = "./textures/Stone.xpm";
    char        *path = "./textures/eagle.png";
	int 		img_width;
	int 		img_height;

	img_width = 100;
    img_height = 100;

    mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 800, 600, "Hello Pajarito");
	img0 = mlx_xpm_file_to_image(mlx, path0, &img_width, &img_height);
    img = mlx_png_file_to_image(mlx, path, &img_width, &img_height);
    mlx_put_image_to_window(mlx, mlx_win, img0, 100, 100);
    mlx_put_image_to_window(mlx, mlx_win, img, 350, 250);
    mlx_loop(mlx);
}
*/

// compile gcc main.c -Wall -Wextra -Werror -Lmlx -lmlx -framework OpenGL -framework AppKit
// It must have to do make into the mlx folder in order to get libmlx.dylib library, 
// and put it in the root of the project




