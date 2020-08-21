#include "cub3d.h"

void	ft_reset_input(t_game_file *game_file)
{
	game_file->ceiling.red = -1;
	game_file->ceiling.green = -1;
	game_file->ceiling.blue = -1;
	game_file->floor.red = -1;
	game_file->floor.green = -1;
	game_file->floor.blue = -1;
	game_file->win_size.width = -1;
	game_file->win_size.height = -1;
	game_file->no_path = NULL;
	game_file->so_path = NULL;
	game_file->ea_path = NULL;
	game_file->we_path = NULL;
	game_file->sprite_path = NULL;
	game_file->map.matrix = NULL;
	game_file->map.orientation = '\0';
	game_file->map.start_pos.x = -1;
	game_file->map.start_pos.y = -1;
}

void		ft_clean_game(t_screen *screen, t_player *player)
{
	screen->mlx = NULL;
	screen->window = NULL;
	screen->win_data.image = NULL;
	screen->north.address = NULL;
	screen->south.address = NULL;
	screen->west.address = NULL;
	screen->east.address = NULL;
	screen->sprite.address = NULL;
	player->move.front = 0;
	player->move.back = 0;
	player->move.right = 0;
	player->move.left = 0;
	player->rotate.right = 0;
	player->rotate.left = 0;
	player->orientation.x = 0;
	player->orientation.y = 0;
	player->plane.x = 0;
	player->plane.y = 0;
}
