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
	if (player->move.front)
		ft_back_front_move(map, player, player->move.front);
	if (player->move.back)
		ft_back_front_move(map, player, -player->move.back);
	if (player->move.left)
		ft_left_right_move(map, player, -player->move.left);
	if (player->move.right)
		ft_left_right_move(map, player, player->move.right);
	if (player->rotate.left)
		ft_rotate_move(player, -player->rotate.left);
	if (player->rotate.right)
		ft_rotate_move(player, player->rotate.right);
	return (0);
}
