#include "cub3d.h"

void		ft_put_pixel(t_texture *texture, int x, int y, int color)
{
	char	*dst;
	////printf("address %p y %d size %d  bits_per_pixel %d\n", texture->address, y, texture-> size_line, texture->bits_per_pixel);
	dst = texture->address + (y * texture->size_line +
		x * (texture->bits_per_pixel / EIGHT_BITS));
	*(unsigned int*)dst = color;
}

int			ft_get_color(t_texture texture, t_wall wall)
{
	int		color;
	char	*dst;

	dst = texture.address + ((int)wall.pos.y * texture.size_line +
		((int)wall.pos.x * (texture.bits_per_pixel / EIGHT_BITS)));
	color = *(unsigned int*)dst;
	return (color);
}

t_texture		ft_get_textures(t_screen screen, t_ray *ray)
{
	t_texture	texture;
	if (ray->side == 0)
	{
		if (ray->dir.x < 0){
		////printf("choosed texture West address %p.width %d, texture height %d, bpp %d , size %d \n"  ,screen.west.address, screen.west.width, screen.west.height, screen.west.bits_per_pixel, screen.west.size_line);
			texture = screen.west;
		}
		else{
		////printf("choosed  texture Est address %p. width %d, texture height %d, bpp %d , size %d \n"  ,screen.east.address, screen.east.width, screen.east.height, screen.east.bits_per_pixel, screen.east.size_line);
			texture = screen.east;
		}
	}
	else
	{
		if (ray->dir.y < 0){
	////printf("choosed texture North address %p. width %d, texture height %d, bpp %d , size %d \n" ,screen.north.address, screen.north.width, screen.north.height, screen.north.bits_per_pixel, screen.north.size_line);
			texture = screen.north;
		}
		else{
	////printf("choosed texture south address %p. width %d, texture height %d, bpp %d , size %d \n"  ,screen.south.address, screen.south.width, screen.south.height, screen.south.bits_per_pixel, screen.south.size_line);
			texture = screen.south;
		}
	}
	return(texture);
}

/*
** - texture->step_size = How much to increase the texture coordinate
**	 per screen pixel.
** - texture->start_pos = Starting texture coordinate.
**
*/

void	ft_draw_walls(t_ray *ray, t_screen *screen, int x)// name of function render wall??
{
	int y;
	int color;
	t_texture texture;

	screen->wall.step = 1.0 * TEXTURE_HEIGHT / ray->line_height;
	screen->wall.start_pos = (ray->draw_start - screen->win_size.height / 2 +
		ray->line_height / 2) * screen->wall.step;
	y = ray->draw_start;

	//printf("draw_start:%d ray->draw_end:%d, X:%d\n", ray->draw_start,ray->draw_end, x);
	while (y < ray->draw_end)
	{
		screen->wall.pos.y = (int)screen->wall.start_pos & (TEXTURE_HEIGHT - 1);
		screen->wall.start_pos += screen->wall.step;
		texture = ft_get_textures(*screen, ray);
		color = ft_get_color(texture, screen->wall);
		if (ray->side == 1)
			color = (color >> 1) & DARKER;//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		ft_put_pixel(&screen->win_data, x, y, color);
		y++;
	}
}