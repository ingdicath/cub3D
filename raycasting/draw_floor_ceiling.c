/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_floor_ceiling.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:50:17 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/25 10:06:06 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		ft_rgb_calculator(int r, int g, int b)
{
	return (r * RED_BIT + g * GREEN_BIT + b);
}

void	ft_set_floor_ceiling(t_game_file file, t_screen *screen)
{
	screen->floor = ft_rgb_calculator(file.floor.red, file.floor.green,
		file.floor.blue);
	screen->ceiling = ft_rgb_calculator(file.ceiling.red, file.ceiling.green,
		file.ceiling.blue);
}

void	ft_draw_floor_ceiling(t_screen *screen, t_ray ray, int x)
{
	int	y;

	y = 0;
	while (y < ray.draw_start)
	{
		ft_put_pixel(&screen->win_data, x, y, screen->ceiling);
		y++;
	}
	y = ray.draw_end;
	while (y < screen->resolution.height)
	{
		ft_put_pixel(&screen->win_data, x, y, screen->floor);
		y++;
	}
}
