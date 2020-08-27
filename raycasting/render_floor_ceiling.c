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

#include "../cub3d.h"

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
