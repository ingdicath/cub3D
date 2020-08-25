/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_orientation.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 13:48:24 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/25 13:51:58 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** current_pos.x += 0.5 to allow player move
*/

int		ft_set_orientation(t_map map, t_player *player)
{
	player->current_pos = map.start_pos;
	if (map.orientation == 'N')
	{
		player->orientation.y = -1;
		player->plane.x = 0.66;
	}
	else if (map.orientation == 'S')
	{
		player->orientation.y = 1;
		player->plane.x = -0.66;
	}
	else if (map.orientation == 'W')
	{
		player->orientation.x = -1;
		player->plane.y = -0.66;
	}
	else if (map.orientation == 'E')
	{
		player->orientation.x = 1;
		player->plane.y = 0.66;
	}
	player->current_pos.x += 0.5;
	player->current_pos.y += 0.5;
	return (1);
}
