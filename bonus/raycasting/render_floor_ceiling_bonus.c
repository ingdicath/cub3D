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

	y = 0;
	while (y < screen->resolution.height)
	{
		player->floor_ray.is_floor = y > (screen->resolution.height / 2
									+ player->ray.pitch);
		ft_set_ray_pos_floor(*screen, player, y);
		ft_draw_floor_ceiling(screen, &player->floor_ray, y);
		y++;
	}
}

void			ft_set_ray_pos_floor(t_screen screen, t_player *player, int y)
{
	player->floor_ray.ray_dir0.x = player->orientation.x - player->plane.x;
	player->floor_ray.ray_dir0.y = player->orientation.y - player->plane.y;
	player->floor_ray.ray_dir1.x = player->orientation.x + player->plane.x;
	player->floor_ray.ray_dir1.y = player->orientation.y + player->plane.y;
	if (player->floor_ray.is_floor)
	{
		player->floor_ray.current_pos = y - screen.resolution.height / 2
			- player->ray.pitch;
		player->ray.cam_z = 0.5 * screen.resolution.height + player->ray.pos_z;
	}
	else
	{
		player->floor_ray.current_pos = screen.resolution.height / 2
			- y + player->ray.pitch;
		player->ray.cam_z = 0.5 * screen.resolution.height - player->ray.pos_z;
	}
	ft_row_distance_step(screen, player);
}

void			ft_row_distance_step(t_screen screen, t_player *player)
{
	player->floor_ray.row_distance = player->ray.cam_z /
										player->floor_ray.current_pos;
	player->floor_ray.step.x = player->floor_ray.row_distance *
		(player->floor_ray.ray_dir1.x - player->floor_ray.ray_dir0.x) /
			screen.resolution.width;
	player->floor_ray.step.y = player->floor_ray.row_distance *
		(player->floor_ray.ray_dir1.y - player->floor_ray.ray_dir0.y) /
			screen.resolution.width;
	player->floor_ray.leftmost.x = player->current_pos.x +
		player->floor_ray.row_distance * player->floor_ray.ray_dir0.x;
	player->floor_ray.leftmost.y = player->current_pos.y +
		player->floor_ray.row_distance * player->floor_ray.ray_dir0.y;
}

void			ft_draw_floor_ceiling(t_screen *screen, t_floor_ray *floor_ray,
					int y)
{
	int			x;
	int			color;

	x = 0;
	while (x < screen->resolution.width)
	{
		ft_calc_fraction_floor_ceiling(screen, floor_ray);
		if (floor_ray->is_floor)
		{
			color = ft_get_color(screen->floor, floor_ray->f_fraction);
			ft_put_pixel(&screen->win_data, x, y, color);
		}
		else
		{
			color = ft_get_color(screen->ceiling, floor_ray->c_fraction);
			ft_put_pixel(&screen->win_data, x, y, color);
		}
		x++;
	}
}

void			ft_calc_fraction_floor_ceiling(t_screen *screen,
					t_floor_ray *floor_ray)
{
	t_position	cell;

	cell.x = (int)(floor_ray->leftmost.x);
	cell.y = (int)(floor_ray->leftmost.y);
	floor_ray->f_fraction.x = (int)(screen->floor.width *
		(floor_ray->leftmost.x - cell.x)) & (screen->floor.width - 1);
	floor_ray->f_fraction.y = (int)(screen->floor.height *
		(floor_ray->leftmost.y - cell.y)) & (screen->floor.height - 1);
	floor_ray->c_fraction.x = (int)(screen->ceiling.width *
		(floor_ray->leftmost.x - cell.x)) & (screen->ceiling.width - 1);
	floor_ray->c_fraction.y = (int)(screen->ceiling.height *
		(floor_ray->leftmost.y - cell.y)) & (screen->ceiling.height - 1);
	floor_ray->leftmost.x += floor_ray->step.x;
	floor_ray->leftmost.y += floor_ray->step.y;
}
