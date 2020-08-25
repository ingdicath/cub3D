/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotations.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:53:13 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/25 13:37:23 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** both camera direction and camera plane must be rotated
*/

void		ft_turn_left(t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->orientation.x;
	old_plane_x = player->plane.x;
	player->orientation.x = player->orientation.x * cos(-ROTATE_SPEED)
		- player->orientation.y * sin(-ROTATE_SPEED);
	player->orientation.y = old_dir_x * sin(-ROTATE_SPEED) +
		player->orientation.y * cos(-ROTATE_SPEED);
	player->plane.x = player->plane.x * cos(-ROTATE_SPEED)
		- player->plane.y * sin(-ROTATE_SPEED);
	player->plane.y = old_plane_x * sin(-ROTATE_SPEED) +
		player->plane.y * cos(-ROTATE_SPEED);
}

void		ft_turn_right(t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->orientation.x;
	old_plane_x = player->plane.x;
	player->orientation.x = player->orientation.x * cos(ROTATE_SPEED)
		- player->orientation.y * sin(ROTATE_SPEED);
	player->orientation.y = old_dir_x * sin(ROTATE_SPEED) +
		player->orientation.y * cos(ROTATE_SPEED);
	player->plane.x = player->plane.x * cos(ROTATE_SPEED)
		- player->plane.y * sin(ROTATE_SPEED);
	player->plane.y = old_plane_x * sin(ROTATE_SPEED) +
		player->plane.y * cos(ROTATE_SPEED);
}
