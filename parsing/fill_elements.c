/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fill_elements.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:46:01 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/26 09:11:36 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		ft_fill_elements(char *line, t_game_file *game_file)
{
	int	result;
	char **line_split;

	line_split = ft_split(line, ' ');
	result = ft_check_valid_file_elements(line_split) &&
		ft_check_resolution(line_split, &game_file->resolution) &&
		ft_check_north_path(line_split, &game_file->no_path) &&
		ft_check_south_path(line_split, &game_file->so_path) &&
		ft_check_east_path(line_split, &game_file->ea_path) &&
		ft_check_west_path(line_split, &game_file->we_path) &&
		ft_check_sprite_path(line_split, &game_file->sprite_path);
	line_split = ft_split(line, ',');
	if (ft_array_size(line_split) > 1)
		result = result && 
	 		ft_check_ceiling(line_split, &game_file->ceiling) &&
	 		ft_check_floor(line_split, &game_file->floor);
	free(line_split);
	return (result);
}

int		ft_check_valid_file_elements(char **line)
{
	if (!line[0] || ft_strcmp(line[0], "C") == 0 ||
		ft_strcmp(line[0], "F") == 0 || ft_strcmp(line[0], "R") == 0 ||
		ft_strcmp(line[0], "NO") == 0 || ft_strcmp(line[0], "SO") == 0 ||
		ft_strcmp(line[0], "WE") == 0 || ft_strcmp(line[0], "EA") == 0 ||
		ft_strcmp(line[0], "S") == 0)
		return (1);
	return (ft_put_error("Missing or invalid element"));
}
