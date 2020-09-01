/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fill_elements.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:46:01 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/28 10:15:26 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int			ft_fill_elements(char *line, t_game_file *game_file, int scrshot)
{
	int		result;
	char	**line_split;
	char	*temp;

	temp = ft_strtrim(line, WHITE_SPACE);
	line_split = ft_split(temp, ' ');
	result = ft_check_valid_file_elements(line_split) &&
		ft_check_resolution(line_split, &game_file->resolution, scrshot) &&
		ft_check_north_path(line_split, &game_file->no_path) &&
		ft_check_south_path(line_split, &game_file->so_path) &&
		ft_check_east_path(line_split, &game_file->ea_path) &&
		ft_check_west_path(line_split, &game_file->we_path) &&
		ft_check_sprite_path(line_split, &game_file->sprite_path) &&
		ft_check_tex_floor(line_split, &game_file->floor_path) &&
		ft_check_tex_ceiling(line_split, &game_file->ceil_path);
	ft_free_array(line_split);
	free(temp);
	return (result);
}

int			ft_check_valid_file_elements(char **line)
{
	if (!line[0] || ft_strcmp_trim(line[0], "C") == 0 ||
		ft_strcmp_trim(line[0], "F") == 0 ||
		ft_strcmp_trim(line[0], "R") == 0 ||
		ft_strcmp_trim(line[0], "NO") == 0 ||
		ft_strcmp_trim(line[0], "SO") == 0 ||
		ft_strcmp_trim(line[0], "WE") == 0 ||
		ft_strcmp_trim(line[0], "EA") == 0 ||
		ft_strcmp_trim(line[0], "S") == 0)
		return (1);
	return (ft_put_error("Missing or invalid element"));
}
