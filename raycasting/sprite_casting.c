#include "../cub3d.h"

//inv_camera  = required for correct matrix multiplication
//sprite_relative = translate sprite position to relative to camera
// transform y = //this is actually the depth inside the screen

// si norminette lo prohibe, enviar solo el juego, t_game
void ft_calc_screen(t_sprite sprite, t_sp_cast *s_cast, t_player player, int w)
{
	double inv_camera;
	t_position sprite_relative;
	t_position transform;

	sprite_relative.x = sprite.position.x - player.current_pos.x;
	sprite_relative.y = sprite.position.y - player.current_pos.y;
	inv_camera = 1.0 / (player.plane.x * player.ray.dir.y -
		player.ray.dir.x * player.plane.y);
	transform.x = inv_camera * (player.ray.dir.y * sprite_relative.x -
		player.ray.dir.x * sprite_relative.y);
	transform.y = inv_camera * (-player.plane.y * sprite_relative.x +
		player.plane.x * sprite_relative.y);
	s_cast->screen_x = (int)(w / 2) * (1 + transform.x / transform.y);
}



int ft_sort_sprites(t_game *game)
{
	int i;
	t_sp_cast s_cast;

	i = 0;
	while (i < game->map.num_sprites)
	{
		ft_calc_screen(game->map.sprites[i], &s_cast, game->player,
			game->screen.win_size.width);
		i++;
	}
	return (0);
}