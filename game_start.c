#include "cub3d.h"
#include <stdio.h> //borrar

int	ft_is_moving(t_movements move, t_rotations rotate)
{
	return (move.front || move.back || move.left
		|| move.right || rotate.right || rotate.left);
}

int	ft_play_game(t_game *game)
{
	if (ft_is_moving(game->player.move, game->player.rotate))
	{
		ft_manage_movements(game->map, &game->player);
		ft_render_map(game);
		// printf("posicion %f %f\n", game->player.current_pos.x, game->player.current_pos.y);
		// printf("plano %f %f\n", game->player.plane.x, game->player.plane.y);
	}
	return (0);
}

int			ft_start_game(t_game_file file)
{
	t_game	game;

	ft_set_game(file, &game);
	mlx_hook(game.screen.window, DESTROY, NOTIFY_MASK, &ft_close_game, &game);
	mlx_hook(game.screen.window, PRESS, PRESS_MASK, &ft_key_press, &game);
	mlx_hook(game.screen.window, RELEASE, RELEASE_MASK, &ft_key_release, &game);
	mlx_loop_hook(game.screen.mlx, &ft_play_game, &game);
	mlx_loop(game.screen.mlx);
	return (0);
}