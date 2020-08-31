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

#include "../cub3d_bonus.h"

int			ft_start_game(t_game_file file)
{
	t_game	game;

	ft_set_game(file, &game, 0);
	mlx_hook(game.screen.window, DESTROY, NOTIFY_MASK, &ft_close_game, &game);
	mlx_hook(game.screen.window, PRESS, PRESS_MASK, &ft_key_press, &game);
	mlx_hook(game.screen.window, RELEASE, RELEASE_MSK, &ft_key_release, &game);
	mlx_hook(game.screen.window, MOTION, MOTION_MASK, &ft_mouse_move, &game);
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
		game->player.rotate.mouse_base.x = game->player.rotate.mouse_look.x;
		game->player.rotate.mouse_base.y = game->player.rotate.mouse_look.y;
		if (game->player.ray.pitch > 0)
			game->player.ray.pitch = ft_max(0, game->player.ray.pitch -
					100 * MOVE_SPEED);
		else if (game->player.ray.pitch < 0)
			game->player.ray.pitch = ft_min(0, game->player.ray.pitch +
					100 * MOVE_SPEED);
		if (game->player.ray.pos_z > 0)
			game->player.ray.pos_z = ft_max(0, game->player.ray.pos_z -
					100 * MOVE_SPEED);
		else if (game->player.ray.pos_z < 0)
			game->player.ray.pos_z = ft_min(0, game->player.ray.pos_z +
					100 * MOVE_SPEED);
	}
	return (0);
}

int			ft_is_moving(t_movements move, t_rotations rotate)
{
	return (move.front || move.back || move.left || move.jump || move.crouch ||
		move.right || rotate.up || rotate.down || rotate.right ||
		rotate.left || rotate.mouse_base.x != rotate.mouse_look.x ||
		rotate.mouse_base.y != rotate.mouse_look.y);
}

int			ft_manage_movements(t_map map, t_player *player)
{
	if (player->move.front)
		ft_back_front_move(map, player, 1);
	if (player->move.back)
		ft_back_front_move(map, player, -1);
	if (player->move.left)
		ft_left_right_move(map, player, -1);
	if (player->move.right)
		ft_left_right_move(map, player, 1);
	if (player->move.jump)
		ft_jump_crouch_move(&player->ray, 1);
	if (player->move.crouch)
		ft_jump_crouch_move(&player->ray, -1);
	if (player->rotate.up ||
		player->rotate.mouse_look.y < player->rotate.mouse_base.y)
		ft_up_down_look(&player->ray, 1);
	if (player->rotate.down ||
		player->rotate.mouse_look.y > player->rotate.mouse_base.y)
		ft_up_down_look(&player->ray, -1);
	if (player->rotate.left ||
		player->rotate.mouse_look.x < player->rotate.mouse_base.x)
		ft_rotate_move(player, -1);
	if (player->rotate.right ||
		player->rotate.mouse_look.x > player->rotate.mouse_base.x)
		ft_rotate_move(player, 1);
	return (0);
}
