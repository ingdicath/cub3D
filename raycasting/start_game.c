/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_game.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:51:02 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/27 17:18:08 by dsalaman      ########   odam.nl         */
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
		mlx_put_image_to_window(game->screen.mlx, game->screen.window,
		game->screen.win_data.image, 0, 0);
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

int			ft_manage_movements(t_map map, t_player *player)
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
