/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fill_elements.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:46:01 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/25 13:09:53 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		ft_fill_elements(char **line_split, t_game_file *game_file)
{
	int	result;

	result = ft_check_resolution(line_split, &game_file->resolution)
	&& ft_check_ceiling(line_split, &game_file->ceiling)
	&& ft_check_floor(line_split, &game_file->floor)
	&& ft_check_north_path(line_split, &game_file->no_path)
	&& ft_check_south_path(line_split, &game_file->so_path)
	&& ft_check_east_path(line_split, &game_file->ea_path)
	&& ft_check_west_path(line_split, &game_file->we_path)
	&& ft_check_sprite_path(line_split, &game_file->sprite_path);
	return (result);
}


//poner funcion que valide que no hayan otros elementos diferentes en el mapa