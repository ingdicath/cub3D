#include "../cub3d.h"

int			ft_set_texture(void *mlx, char *path, t_texture *texture)
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

int			ft_set_all_textures(t_game_file file, t_screen *screen)
{
	int		result;

	result = ft_set_texture(screen->mlx, file.no_path, &screen->north)
	&& ft_set_texture(screen->mlx, file.so_path, &screen->south)
	&& ft_set_texture(screen->mlx, file.we_path, &screen->west)
	&& ft_set_texture(screen->mlx, file.ea_path, &screen->east)
	&& ft_set_texture(screen->mlx, file.sprite_path, &screen->sprite);
	return (result);
}

int			ft_set_orientation(t_map map, t_player *player)
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

	// Opcional (Magia!!!)
	player->current_pos.x += 0.5;
	player->current_pos.y += 0.5;


	// if (player->direction.y == 0)
	// 	player->plane.y = 0.66 ;
	// else
	// 	player->plane.x = 0.66 ;
	return (1);
}


int				ft_set_screen(t_screen *screen)
{
	t_texture	*data;

	//printf("init resolution w:%d h:%d\n", screen->resolution.width, screen->resolution.height); //borrar
	data = &screen->win_data;
	screen->mlx = mlx_init();
	if (screen->mlx == NULL)
		return (ft_put_error("mlx connection failure"));
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

/*
** Initializing the game screen
**
** @param t_game_file file: 	the input file (e.g. "file.cub" validated)
** @param t_game *game: 		the game instance
**
** @return int:					1 is ok
*/

int ft_set_game(t_game_file file, t_game *game)
{
	game->map = file.map;
	game->screen.resolution = file.resolution;

	ft_clean_game(&game->screen, &game->player, &game->map);
	if (!ft_set_screen(&game->screen))
		ft_put_error("set screen failure"); // ok
	ft_set_floor_ceiling(file, &game->screen);//ok
	ft_set_all_textures(file, &game->screen); //ok
	ft_set_orientation(game->map, &game->player);
	ft_render_map(game);
	return(1);
}