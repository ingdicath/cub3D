/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculate_wall_draw.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:49:44 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/25 10:04:05 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** Draw the pixels of the stripe as a vertical line.
** - ray->wall_x = where exactly the wall was hit. This is required to know
** 	 which x-coordinate of the texture we have to use.
** - wall->pos.x = is the x-coordinate of the texture, and this is calculated
**	out of wall_x.
*/

void	ft_calc_wall_pos(t_ray *ray, t_wall *wall, t_position current)
{
	if (ray->side == 0)
		ray->wall_x = current.y + ray->perpwalldist * ray->dir.y;
	else
		ray->wall_x = current.x + ray->perpwalldist * ray->dir.x;
	ray->wall_x -= floor(ray->wall_x);
	wall->pos.x = (int)(ray->wall_x * (double)TEXTURE_WIDTH);
	if ((ray->side == 0 && ray->dir.x > 0)
		|| (ray->side == 1 && ray->dir.y < 0))
		wall->pos.x = TEXTURE_WIDTH - wall->pos.x - 1;
}

/*
** Calculate height of line to draw on screen the raycasting.
** Calculate lowest and highest pixel to fill in current stripe.
*/

void	ft_calc_draw_limits(t_ray *ray, t_size resolution)
{
	ray->line_height = (int)(resolution.height / ray->perpwalldist);
	ray->draw_start = -ray->line_height / 2 + resolution.height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (ray->line_height / 2) + (resolution.height / 2);
	if (ray->draw_end >= resolution.height)
		ray->draw_end = resolution.height - 1;
}

/*
** Creating the raycasting
** int hit = 0; //was there a wall hit?
** int side; //was a NS or a EW wall hit?
** Calculate distance projected on camera direction
**    (Euclidean distance will give fisheye effect!)
** perpWallDist: the length of this line is the value to compute now,
** the distance perpendicular from the wall hit point to the camera plane
** instead of Euclidean distance to the player point, to avoid making straight
** walls look rounded.
*/

void	ft_calc_wall_dist(t_ray *ray, t_position current)
{
	if (ray->side == 0)
		ray->perpwalldist = (ray->map.x - current.x +
			(1 - ray->step.x) / 2) / ray->dir.x;
	else
		ray->perpwalldist = (ray->map.y - current.y +
			(1 - ray->step.y) / 2) / ray->dir.y;
	if (ray->perpwalldist < 1)
		ray->perpwalldist = 1;
	else
		ray->perpwalldist = ray->perpwalldist;
}
