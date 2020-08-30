/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_game.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:55:32 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/27 17:04:36 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int				ft_set_game(t_game_file file, t_game *game, int screenshot)
{
	game->map = file.map;
	game->screen.resolution = file.resolution;
	ft_clean_game(game->screen.resolution, &game->player, &game->map);
	if (!ft_set_screen(&game->screen, screenshot))
		ft_put_error("set screen failure");
	ft_set_all_textures(file, &game->screen);
	ft_set_orientation(game->map, &game->player);
	ft_render_floor_ceiling(&game->screen, &game->player);
	ft_render_map(game);
	return (1);
}

int				ft_set_screen(t_screen *screen, int screenshot)
{
	t_texture	*data;

	data = &screen->win_data;
	screen->mlx = mlx_init();
	if (screen->mlx == NULL)
		return (ft_put_error("mlx connection failure"));
	if (screenshot == 0)
		ft_resize_resolution(screen);
	screen->window = mlx_new_window(screen->mlx,
		screen->resolution.width, screen->resolution.height, "Cub3D - bonus");
	if (screen->window == NULL)
		return (ft_put_error("mlx window failure"));
	data->image = mlx_new_image(screen->mlx,
		screen->resolution.width, screen->resolution.height);
	if (data->image == NULL)
		return (ft_put_error("mlx image failure"));
	data->address = mlx_get_data_addr(data->image, &data->bits_per_pixel,
		&data->size_line, &data->endian);
	if (data->address == NULL)
		return (ft_put_error("mlx address image failure"));
	return (1);
}

int				ft_set_all_textures(t_game_file file, t_screen *screen)
{
	int			result;

	result = ft_set_texture(screen->mlx, file.no_path, &screen->north)
	&& ft_set_texture(screen->mlx, file.so_path, &screen->south)
	&& ft_set_texture(screen->mlx, file.we_path, &screen->west)
	&& ft_set_texture(screen->mlx, file.ea_path, &screen->east)
	&& ft_set_texture(screen->mlx, file.sprite_path, &screen->sprite)
	&& ft_set_texture(screen->mlx, file.floor_path, &screen->floor)
	&& ft_set_texture(screen->mlx, file.ceil_path, &screen->ceiling);
	return (result);
}

/*
** current_pos.x += 0.5 to allow player move
*/

int				ft_set_orientation(t_map map, t_player *player)
{
	player->current_pos = map.start_pos;
	if (map.orientation == 'N')
	{
		player->orientation.y = -1;
		player->plane.x = 0.66;
	}
	else if (map.orientation == 'S')
	{
		player->orientation.y = 1;
		player->plane.x = -0.66;
	}
	else if (map.orientation == 'W')
	{
		player->orientation.x = -1;
		player->plane.y = -0.66;
	}
	else if (map.orientation == 'E')
	{
		player->orientation.x = 1;
		player->plane.y = 0.66;
	}
	player->current_pos.x += 0.5;
	player->current_pos.y += 0.5;
	return (1);
}
