/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_start.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:51:02 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/26 08:41:58 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			ft_start_game(t_game_file file)
{
	t_game	game;

	ft_set_game(file, &game, 0);
	mlx_hook(game.screen.window, DESTROY, NOTIFY_MASK, &ft_close_game, &game);
	mlx_hook(game.screen.window, PRESS, PRESS_MASK, &ft_key_press, &game);
	mlx_hook(game.screen.window, RELEASE, RELEASE_MASK, &ft_key_release, &game);
	mlx_loop_hook(game.screen.mlx, &ft_play_game, &game);
	mlx_loop(game.screen.mlx);
	return (0);
}

int			ft_play_game(t_game *game)
{
	if (ft_is_moving(game->player.move, game->player.rotate))
	{
		ft_manage_movements(game->map, &game->player);
		ft_render_map(game);
	}
	return (0);
}

int			ft_is_moving(t_movements move, t_rotations rotate)
{
	return (move.front || move.back || move.left
		|| move.right || rotate.right || rotate.left);
}
