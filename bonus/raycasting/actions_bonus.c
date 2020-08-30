/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:51:42 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/28 10:29:16 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int		ft_key_press(int keycode, t_game *game)
{
	if (keycode == ESC)
		ft_close_game(game);
	if (keycode == KEY_W)
		game->player.move.front = 1;
	if (keycode == KEY_S)
		game->player.move.back = 1;
	if (keycode == KEY_A)
		game->player.move.left = 1;
	if (keycode == KEY_D)
		game->player.move.right = 1;
	if (keycode == RIGHT)
		game->player.rotate.right = 1;
	if (keycode == LEFT)
		game->player.rotate.left = 1;
	return (0);
}

int		ft_close_game(t_game *game)
{
	if (game->screen.window)
		mlx_destroy_window(game->screen.mlx, game->screen.window);
	if (game->screen.win_data.image)
		mlx_destroy_image(game->screen.mlx, game->screen.win_data.image);
	ft_free_memory(&game->map);
	exit(0);
}

int		ft_key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->player.move.front = 0;
	if (keycode == KEY_S)
		game->player.move.back = 0;
	if (keycode == KEY_A)
		game->player.move.left = 0;
	if (keycode == KEY_D)
		game->player.move.right = 0;
	if (keycode == LEFT)
		game->player.rotate.left = 0;
	if (keycode == RIGHT)
		game->player.rotate.right = 0;
	return (0);
}

int		ft_mouse_move(int x, int y, t_game *game)
{
	game->player.rotate.mouse_turn = x;
	return (y);
}