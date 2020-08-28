/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movements.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:54:06 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/28 10:28:12 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** In moves functions, '+' instead '0' is because of the floodfill
** First if: Here it is checked if the movement goes off the map
** Second if: If we want north faced in the north and it is the first position
*/

void			ft_back_front_move(t_map map, t_player *player, int move)
{
	t_position	new_pos;

	new_pos.x = player->current_pos.x + player->orientation.x * MOVE_SPEED *
		move;
	new_pos.y = player->current_pos.y + player->orientation.y * MOVE_SPEED *
		move;
	if (map.matrix[(int)new_pos.y][(int)player->current_pos.x] == '+')
		player->current_pos.y = new_pos.y;
	if (map.matrix[(int)player->current_pos.y][(int)new_pos.x] == '+')
		player->current_pos.x = new_pos.x;
}

void			ft_left_right_move(t_map map, t_player *player, int move)
{
	t_position	new_pos;

	new_pos.x = player->current_pos.x + player->plane.x * MOVE_SPEED *
		move;
	new_pos.y = player->current_pos.y + player->plane.y * MOVE_SPEED *
		move;
	if (map.matrix[(int)new_pos.y][(int)player->current_pos.x] == '+')
		player->current_pos.y = new_pos.y;
	if (map.matrix[(int)player->current_pos.y][(int)new_pos.x] == '+')
		player->current_pos.x = new_pos.x;
}

void			ft_rotate_move(t_player *player, int turn)
{
	double		old_dir_x;
	double		old_plane_x;

	old_dir_x = player->orientation.x;
	old_plane_x = player->plane.x;
	player->orientation.x = player->orientation.x * cos(ROTATE_SPEED * turn)
		+ player->orientation.y * sin(-ROTATE_SPEED * turn);
	player->orientation.y = old_dir_x * sin(ROTATE_SPEED * turn) +
		player->orientation.y * cos(ROTATE_SPEED * turn);
	player->plane.x = player->plane.x * cos(ROTATE_SPEED * turn)
		+ player->plane.y * sin(-ROTATE_SPEED * turn);
	player->plane.y = old_plane_x * sin(ROTATE_SPEED * turn) +
		player->plane.y * cos(ROTATE_SPEED * turn);
}
