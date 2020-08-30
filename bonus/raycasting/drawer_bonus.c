/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:52:26 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/28 10:24:26 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

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

int				ft_get_color(t_texture texture, t_position position)
{
	int			color;
	char		*dst;

	dst = texture.address + ((int)position.y * texture.size_line +
		((int)position.x * (texture.bits_per_pixel / EIGHT_BITS)));
	color = *(unsigned int*)dst;
	return (color);
}

void			ft_put_pixel(t_texture *texture, int x, int y, int color)
{
	char		*dst;

	dst = texture->address + (y * texture->size_line +
		x * (texture->bits_per_pixel / EIGHT_BITS));
	*(unsigned int*)dst = color;
}
