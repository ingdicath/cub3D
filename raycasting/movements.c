/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   movements.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:54:06 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/25 13:23:19 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** In moves functions, '+' instead '0' is because of the floodfill
** First if: Here it is checked if the movement goes off the map
** Second if: If we want north in north and it is the first position
*/

void			ft_move_front(t_map map, t_player *player)
{
	t_position	new_pos;

	new_pos.x = player->current_pos.x + player->orientation.x * MOVE_SPEED;
	new_pos.y = player->current_pos.y + player->orientation.y * MOVE_SPEED;
	if (map.matrix[(int)new_pos.y][(int)player->current_pos.x] == '+')
		player->current_pos.y = new_pos.y;
	if (map.matrix[(int)player->current_pos.y][(int)new_pos.x] == '+')
		player->current_pos.x = new_pos.x;
}

void			ft_move_back(t_map map, t_player *player)
{
	t_position	new_pos;

	new_pos.x = player->current_pos.x - player->orientation.x * MOVE_SPEED;
	new_pos.y = player->current_pos.y - player->orientation.y * MOVE_SPEED;
	
	int x = (int)floor((new_pos.x));
	int y = (int)floor((new_pos.y));

	if( x > 0 && map.matrix[(int)new_pos.y][x] != '\0'  
		&&	map.matrix[(int)new_pos.y][(int)player->current_pos.x] == '+')
		player->current_pos.y = new_pos.y;
	
	if (y > 0 && map.matrix[y] != NULL  &&
		map.matrix[(int)player->current_pos.y][(int)new_pos.x] == '+')
		player->current_pos.x = new_pos.x;
}

void			ft_move_right(t_map map, t_player *player)
{
	t_position	new_pos;

	new_pos.x = player->current_pos.x + player->plane.x * MOVE_SPEED;
	new_pos.y = player->current_pos.y + player->plane.y * MOVE_SPEED;
	if (map.matrix[(int)new_pos.y][(int)player->current_pos.x] == '+')
		player->current_pos.y = new_pos.y;
	if (map.matrix[(int)player->current_pos.y][(int)new_pos.x] == '+')
		player->current_pos.x = new_pos.x;
}

void			ft_move_left(t_map map, t_player *player)
{
	t_position	new_pos;

	new_pos.x = player->current_pos.x - player->plane.x * MOVE_SPEED;
	new_pos.y = player->current_pos.y - player->plane.y * MOVE_SPEED;
	if (map.matrix[(int)new_pos.y][(int)player->current_pos.x] == '+')
		player->current_pos.y = new_pos.y;
	if (map.matrix[(int)player->current_pos.y][(int)new_pos.x] == '+')
		player->current_pos.x = new_pos.x;
}

int				ft_manage_movements(t_map map, t_player *player)
{
	if (player->move.front == 1)
		ft_move_front(map, player);
	if (player->move.back == 1)
		ft_move_back(map, player);
	if (player->move.left == 1)
		ft_move_left(map, player);
	if (player->move.right == 1)
		ft_move_right(map, player);
	if (player->rotate.left == 1)
		ft_turn_left(player);
	if (player->rotate.right == 1)
		ft_turn_right(player);
	return (0);
}
