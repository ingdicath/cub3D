/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_game.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:55:32 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/25 13:50:02 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int				ft_set_game(t_game_file file, t_game *game)
{
	game->map = file.map;
	game->screen.resolution = file.resolution;
	ft_clean_game(&game->screen, &game->player, &game->map);
	if (!ft_set_screen(&game->screen))
		ft_put_error("set screen failure");
	ft_set_floor_ceiling(file, &game->screen);
	ft_set_all_textures(file, &game->screen);
	ft_set_orientation(game->map, &game->player);
	ft_render_map(game);
	return (1);
}

int				ft_set_screen(t_screen *screen)
{
	t_texture	*data;

	data = &screen->win_data;
	screen->mlx = mlx_init();
	if (screen->mlx == NULL)
		return (ft_put_error("mlx connection failure"));
	// incuir una condicion  que diga que si hay screenshot no haga resize
	ft_resize_resolution(screen);
	screen->window = mlx_new_window(screen->mlx,
		screen->resolution.width, screen->resolution.height, "Welcome");
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

int				ft_resize_resolution(t_screen *screen)
{
	mlx_get_screen_size(screen->mlx, &screen->max_res.width,
		&screen->max_res.height);
	if (screen->max_res.width <= 0 || screen->max_res.height <= 0)
		return (ft_put_error("mlx screen resolution failure"));
	if (screen->resolution.width > screen->max_res.width)
		screen->resolution.width = screen->max_res.width;
	if (screen->resolution.height > screen->max_res.height)
		screen->resolution.height = screen->max_res.height;
	return (1);
}

int				ft_set_texture(void *mlx, char *path, t_texture *texture)
{
	texture->image = mlx_xpm_file_to_image(mlx, path,
		&texture->width, &texture->height);
	if (texture->image == NULL)
		return (ft_put_error("invalid path for texture"));
	texture->address = mlx_get_data_addr(texture->image,
		&texture->bits_per_pixel, &texture->size_line, &texture->endian);
	if (texture->address == NULL)
		return (ft_put_error("image for texture failure"));
	return (1);
}

int				ft_set_all_textures(t_game_file file, t_screen *screen)
{
	int			result;

	result = ft_set_texture(screen->mlx, file.no_path, &screen->north)
	&& ft_set_texture(screen->mlx, file.so_path, &screen->south)
	&& ft_set_texture(screen->mlx, file.we_path, &screen->west)
	&& ft_set_texture(screen->mlx, file.ea_path, &screen->east)
	&& ft_set_texture(screen->mlx, file.sprite_path, &screen->sprite);
	return (result);
}
