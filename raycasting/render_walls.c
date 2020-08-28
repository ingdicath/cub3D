/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_walls.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:49:44 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/28 10:22:29 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** Calculate distance projected on camera direction
**    (Euclidean distance will give fisheye effect!)
** perpWallDist: the length of this line is the value to compute now,
** the distance perpendicular from the wall hit point to the camera plane
** instead of Euclidean distance to the player point, to avoid making straight
** walls look rounded.
*/

void			ft_calc_wall_dist(t_ray *ray, t_position current)
{
	if (ray->side == 0)
		ray->perpwalldist = (ray->map.x - current.x +
			(1 - ray->step.x) / 2) / ray->dir.x;
	else
		ray->perpwalldist = (ray->map.y - current.y +
			(1 - ray->step.y) / 2) / ray->dir.y;
}

/*
** Calculate height of line to draw on screen the raycasting.
** Calculate lowest and highest pixel to fill in current stripe.
*/

void			ft_calc_draw_limits(t_ray *ray, t_size resolution)
{
	ray->line_height = (int)(resolution.height / ray->perpwalldist);
	ray->draw_start = resolution.height / 2 - ray->line_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = resolution.height / 2 + ray->line_height / 2;
	if (ray->draw_end < 0)
		ray->draw_end = resolution.height;
	if (ray->draw_end >= resolution.height)
		ray->draw_end = resolution.height - 1;
}

/*
** Draw the pixels of the stripe as a vertical line.
** - ray->wall_x = where exactly the wall was hit. This is required to know
** 	 which x-coordinate of the texture we have to use.
** - wall->pos.x = is the x-coordinate of the texture, and this is calculated
**	out of wall_x.
*/

void			ft_calc_wall_pos(t_ray *ray, t_screen *screen,
					t_position current)
{
	t_texture	texture;

	texture = ft_get_textures(*screen, ray);
	if (ray->side == 0)
		ray->wall_x = current.y + ray->perpwalldist * ray->dir.y;
	else
		ray->wall_x = current.x + ray->perpwalldist * ray->dir.x;
	ray->wall_x -= floor(ray->wall_x);
	screen->wall.pos.x = (int)(ray->wall_x * texture.width);
	if ((ray->side == 0 && ray->dir.x > 0)
		|| (ray->side == 1 && ray->dir.y < 0))
		screen->wall.pos.x = (int)(texture.width - screen->wall.pos.x - 1);
}

/*
** DARKER makes color darker for y-sides: R, G and B byte each divided
** through two with a "shift" and an "and".
*/

void			ft_draw_walls(t_ray *ray, t_screen *screen, int x)
{
	int			y;
	int			color;
	t_texture	texture;

	texture = ft_get_textures(*screen, ray);
	screen->wall.step = 1.0 * texture.height / ray->line_height;
	screen->wall.start_pos = (ray->draw_start - screen->resolution.height / 2 +
		ray->line_height / 2) * screen->wall.step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		screen->wall.pos.y = (int)screen->wall.start_pos & (texture.height - 1);
		screen->wall.start_pos += screen->wall.step;
		color = ft_get_color(texture, screen->wall.pos);
		if (ray->side == 1)
			color = (color >> 1) & DARKER;
		ft_put_pixel(&screen->win_data, x, y, color);
		y++;
	}
}
