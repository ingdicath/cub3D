/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_walls.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:52:26 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/27 08:45:19 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void			ft_put_pixel(t_texture *texture, int x, int y, int color)
{
	char		*dst;

	dst = texture->address + (y * texture->size_line +
		x * (texture->bits_per_pixel / EIGHT_BITS));
	*(unsigned int*)dst = color;
}

int				ft_get_color(t_texture texture, t_position position)
{
	int			color;
	char		*dst;

	dst = texture.address + ((int)position.y * texture.size_line +
		((int)position.x * (texture.bits_per_pixel / EIGHT_BITS)));
	color = *(unsigned int*)dst;
	return (color);
}

t_texture		ft_get_textures(t_screen screen, t_ray *ray)
{
	t_texture	texture;

	if (ray->side == 0)
	{
		if (ray->dir.x < 0)
			texture = screen.west;
		else
			texture = screen.east;
	}
	else
	{
		if (ray->dir.y < 0)
			texture = screen.north;
		else
			texture = screen.south;
	}
	return (texture);
}

/*
** - texture->step_size = How much to increase the texture coordinate
**	 per screen pixel.
** - texture->start_pos = Starting texture coordinate.
** - DARKER; make color darker for y-sides: R, G and B byte each divided
** 	 through two with a "shift" and an "and"
*/

void			ft_draw_walls(t_ray *ray, t_screen *screen, int x)
{
	int			y;
	int			color;
	t_texture	texture;

	screen->wall.step = 1.0 * TEXTURE_HEIGHT / ray->line_height;
	screen->wall.start_pos = (ray->draw_start - screen->resolution.height / 2 +
		ray->line_height / 2) * screen->wall.step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		screen->wall.pos.y = (int)screen->wall.start_pos & (TEXTURE_HEIGHT - 1);
		screen->wall.start_pos += screen->wall.step;
		texture = ft_get_textures(*screen, ray);
		color = ft_get_color(texture, screen->wall.pos);
		if (ray->side == 1)
			color = (color >> 1) & DARKER;
		ft_put_pixel(&screen->win_data, x, y, color);
		y++;
	}
}
