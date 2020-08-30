/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_floor_ceiling.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:50:17 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/27 16:59:36 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void			ft_render_floor_ceiling(t_screen *screen, t_player *player)
{
	int			y;

	y = screen->resolution.height / 2 + 1;
	while(y < screen->resolution.height)
	{
		ft_set_ray_pos_floor(*screen, player, y);
		ft_draw_floor_ceiling(screen, &player->floor_ray, y);
		y++;
	}
}

void			ft_set_ray_pos_floor(t_screen screen, t_player *player, int y)
{
	double		ray_dir0_x;
	double		ray_dir0_y;
	double		ray_dir1_x;
	double		ray_dir1_y;
	double		pos_z;

	ray_dir0_x = player->orientation.x - player->plane.x;
	ray_dir0_y = player->orientation.y - player->plane.y;
	ray_dir1_x = player->orientation.x + player->plane.x;
	ray_dir1_y = player->orientation.y + player->plane.y;
	player->floor_ray.current_pos = y - screen.resolution.height / 2;
	pos_z = 0.5 * screen.resolution.height;
	player->floor_ray.row_distance = pos_z / player->floor_ray.current_pos;
	player->floor_ray.step.x = player->floor_ray.row_distance *
		(ray_dir1_x - ray_dir0_x) / screen.resolution.width;
	player->floor_ray.step.y = player->floor_ray.row_distance *
		(ray_dir1_y - ray_dir0_y) / screen.resolution.width;
	player->floor_ray.leftmost.x = player->current_pos.x +
		player->floor_ray.row_distance * ray_dir0_x;
	player->floor_ray.leftmost.y = player->current_pos.y +
		player->floor_ray.row_distance * ray_dir0_y;
}

void			ft_draw_floor_ceiling(t_screen *screen, t_floor_ray *floor_ray,
					int y)
{
	int			x;
	int			color;
	t_position	cell;

	x = 0;
	while (x < screen->resolution.width)
	{
		cell.x = (int)(floor_ray->leftmost.x);
		cell.y = (int)(floor_ray->leftmost.y);
		floor_ray->f_fraction.x = (int)(screen->floor.width *
			(floor_ray->leftmost.x - cell.x)) & (screen->floor.width - 1);
		floor_ray->f_fraction.y = (int)(screen->floor.height *
			(floor_ray->leftmost.y - cell.y)) & (screen->floor.height - 1);
		floor_ray->c_fraction.x = (int)(screen->floor.width *
			(floor_ray->leftmost.x - cell.x)) & (screen->ceiling.width - 1);
		floor_ray->c_fraction.y = (int)(screen->floor.height *
			(floor_ray->leftmost.y - cell.y)) & (screen->ceiling.height - 1);
		floor_ray->leftmost.x += floor_ray->step.x;
		floor_ray->leftmost.y += floor_ray->step.y;
		color = ft_get_color(screen->floor, floor_ray->f_fraction);
		ft_put_pixel(&screen->win_data, x, y, color);
		color = ft_get_color(screen->ceiling, floor_ray->c_fraction);
		ft_put_pixel(&screen->win_data, x, (screen->resolution.height - y -1), color);
		x++;
	}
}
