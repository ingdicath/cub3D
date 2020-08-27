/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_map.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:54:32 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/25 13:35:17 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		ft_render_map(t_game *game)
{
	int		x;

	x = 0;
	while (x < game->screen.resolution.width)
	{
		ft_set_ray_position(game, x);
		ft_calc_side_dist(game->player.current_pos, &game->player.ray);
		ft_perform_dda(game->map, &game->player.ray);
		ft_calc_wall_dist(&game->player.ray, game->player.current_pos);
		ft_calc_draw_limits(&game->player.ray, game->screen.resolution);
		ft_calc_wall_pos(&game->player.ray, &game->screen,
			game->player.current_pos);
		ft_draw_walls(&game->player.ray, &game->screen, x);
		ft_draw_floor_ceiling(&game->screen, game->player.ray, x);
		game->map.zbuffer[x] = game->player.ray.perpwalldist;
		x++;
	}
	ft_render_sprites(game);
	mlx_put_image_to_window(game->screen.mlx, game->screen.window,
		game->screen.win_data.image, 0, 0);
}

void		ft_set_ray_position(t_game *game, int x)
{
	t_ray	*ray;

	ray = &game->player.ray;
	ray->camera_x = 2 * x / (double)game->screen.resolution.width - 1;
	ray->dir.x = game->player.orientation.x +
			game->player.plane.x * ray->camera_x;
	ray->dir.y = game->player.orientation.y +
			game->player.plane.y * ray->camera_x;
	ray->map.x = (int)game->player.current_pos.x;
	ray->map.y = (int)game->player.current_pos.y;
	ray->deltadist.x = fabs(1.0 / ray->dir.x);
	ray->deltadist.y = fabs(1.0 / ray->dir.y);
}

void		ft_calc_side_dist(t_position current, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->sidedist.x = (current.x - ray->map.x) * ray->deltadist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->sidedist.x = (ray->map.x + 1.0 - current.x) * ray->deltadist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->sidedist.y = (current.y - ray->map.y) * ray->deltadist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sidedist.y = (ray->map.y + 1.0 - current.y) * ray->deltadist.y;
	}
}

/*
** map.matrix[y][x] in this order of x and y, North face up
*/

void		ft_perform_dda(t_map map, t_ray *ray)
{
	int		hit;
	int		x;
	int		y;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedist.x < ray->sidedist.y)
		{
			ray->sidedist.x += ray->deltadist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist.y += ray->deltadist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		x = (int)ray->map.x;
		y = (int)ray->map.y;
		if (y < 0 || x < 0 || map.matrix[y][x] == '1')
			hit = 1;
	}
}
