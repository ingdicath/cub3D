#include "cub3d.h"

//move forward if no wall in front of you
void			ft_move_front(t_map map, t_player *player)
{
	// //printf("llo que quieras\n");
	t_position	new_pos;

	new_pos.x = player->current_pos.x + player->orientation.x * MOVE_SPEED;
	new_pos.y = player->current_pos.y + player->orientation.y * MOVE_SPEED;

	if (map.matrix[(int)new_pos.y][(int)player->current_pos.x] == '0') // Aca se revisa si el movimiento se sale del mapa 
		player->current_pos.y = new_pos.y;
	if (map.matrix[(int)player->current_pos.y][(int)new_pos.x] == '0') // si queremos el norte en el norte y es la primera posicion
		player->current_pos.x = new_pos.x;
}

//move backwards if no wall behind you
void			ft_move_back(t_map map, t_player *player)
{
	t_position	new_pos;

	new_pos.x = player->current_pos.x - player->orientation.x * MOVE_SPEED;
	new_pos.y = player->current_pos.y - player->orientation.y * MOVE_SPEED;
	if (map.matrix[(int)new_pos.y][(int)player->current_pos.x] == '0')
		player->current_pos.y = new_pos.y;
	if (map.matrix[(int)player->current_pos.y][(int)new_pos.x] == '0')
		player->current_pos.x = new_pos.x;
}

void			ft_move_right(t_map map, t_player *player)
{
	t_position	new_pos;
	new_pos.x = player->current_pos.x + player->plane.x * MOVE_SPEED;
	new_pos.y = player->current_pos.y + player->plane.y * MOVE_SPEED;
	if (map.matrix[(int)new_pos.y][(int)player->current_pos.x] == '0')
		player->current_pos.y = new_pos.y;
	if (map.matrix[(int)player->current_pos.y][(int)new_pos.x] == '0')
		player->current_pos.x = new_pos.x;
}

void			ft_move_left(t_map map, t_player *player)// tarea factorizar
{
	t_position	new_pos;
	new_pos.x = player->current_pos.x - player->plane.x * MOVE_SPEED;
	new_pos.y = player->current_pos.y - player->plane.y * MOVE_SPEED;
	if (map.matrix[(int)new_pos.y][(int)player->current_pos.x] == '0')
		player->current_pos.y = new_pos.y;
	if (map.matrix[(int)player->current_pos.y][(int)new_pos.x] == '0')
		player->current_pos.x = new_pos.x;
}

int		ft_manage_movements(t_map map, t_player *player) //revisar si esta bien definida la posicion
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