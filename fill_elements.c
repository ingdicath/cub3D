#include "cub3d.h"
#include <stdio.h> //borrar

int			ft_fill_elements(char **line_split, t_game_file *game_file)
{
	int		result;

	result = ft_check_resolution(line_split, &game_file->win_size)
	&& ft_check_ceiling(line_split, &game_file->ceiling)
	&& ft_check_floor(line_split, &game_file->floor)
	&& ft_check_north_path(line_split, &game_file->no_path)
	&& ft_check_south_path(line_split, &game_file->so_path)
	&& ft_check_east_path(line_split, &game_file->ea_path)
	&& ft_check_west_path(line_split, &game_file->we_path)
	&& ft_check_sprite_path(line_split, &game_file->sprite_path);
	return (result);
}


int		ft_array_size(char **array)
{
	int i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}