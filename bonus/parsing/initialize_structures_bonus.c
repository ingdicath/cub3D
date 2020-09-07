/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize_structures.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:47:25 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/25 13:10:20 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	ft_reset_input(t_game_file *game_file)
{
	game_file->resolution.width = -1;
	game_file->resolution.height = -1;
	game_file->no_path = NULL;
	game_file->so_path = NULL;
	game_file->ea_path = NULL;
	game_file->we_path = NULL;
	game_file->sprite_path =  (char **)malloc(sizeof(char *) * 1);
	if (game_file->sprite_path == NULL)
		ft_put_error("It is not possible define sprites");
	game_file->sprite_path[0] = NULL;
	game_file->floor_path = NULL;
	game_file->ceil_path = NULL;
	game_file->map.matrix = NULL;
	game_file->map.orientation = '\0';
	game_file->map.start_pos.x = -1;
	game_file->map.start_pos.y = -1;
	game_file->map.num_sprites = 0;
	game_file->map.num_type_sprite = 0;
	ft_initialize_sprites(game_file);
	
}
void 	ft_initialize_sprites(t_game_file *game_file)
{
	int i;

	i = 0;
	game_file->map.type_sprite = (int *)malloc(sizeof(int *) * 10);
	if (game_file->map.type_sprite  == NULL)
		ft_put_error("It is not possible define sprites");
	while(i < 10)
	{
		game_file->map.type_sprite[i] = 0;
		i++;	
	}
}



void	ft_clean_game(t_size resolution, t_player *player, t_map *map)
{
	player->move.front = 0;
	player->move.back = 0;
	player->move.right = 0;
	player->move.left = 0;
	player->move.jump = 0;
	player->move.crouch = 0;
	player->rotate.up = 0;
	player->rotate.down = 0;
	player->rotate.right = 0;
	player->rotate.left = 0;
	player->rotate.mouse_base.x = 0;
	player->rotate.mouse_look.x = 0;
	player->rotate.mouse_base.y = -1;
	player->rotate.mouse_look.y = 0;
	player->orientation.x = 0;
	player->orientation.y = 0;
	player->plane.x = 0;
	player->plane.y = 0;
	player->ray.pitch = 0;
	player->ray.pos_z = 0;
	map->zbuffer = (double *)malloc(sizeof(double) * resolution.width);
	if (map->zbuffer == NULL)
		ft_put_error("It is not possible define size for zbuffer");
}

