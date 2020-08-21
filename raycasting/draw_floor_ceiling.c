#include "../cub3d.h"

int ft_rgb_calculator(int r, int g, int b)
{
	return (r * RED_BIT + g * GREEN_BIT + b);
}

void ft_set_floor_ceiling(t_game_file file, t_screen *screen)
{
	screen->floor = ft_rgb_calculator(file.floor.red, file.floor.green,
		file.floor.blue);
	screen->ceiling = ft_rgb_calculator(file.ceiling.red, file.ceiling.green,
		file.ceiling.blue);
}

void ft_draw_floor_ceiling(t_screen *screen, t_ray ray, int x)
{
	int y;
	
	y = 0;
	//printf("ceiling, floor %d %d\n", screen->ceiling, screen->floor);
	while(y < ray.draw_start)
	{
		ft_put_pixel(&screen->win_data, x, y, screen->ceiling);
		y++;
	}
	y = ray.draw_end;
	while(y < screen->win_size.height)
	{
		ft_put_pixel(&screen->win_data, x, y, screen->floor);
		y++;
	}
}