/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/26 07:32:17 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/26 07:32:35 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				main(int argc, char **argv)
{
	int			screenshot;
	t_game_file	game_file;

	if (!ft_parsing(argc, argv, &game_file, &screenshot))
		return (ft_put_error("Parsing failure"));
	if (screenshot)
		ft_take_screenshot(game_file);
	else
		ft_start_game(game_file);
	return (0);
}
