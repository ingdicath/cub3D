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

#include "../cub3d.h"

int			ft_fill_elements(char *line, t_game_file *game_file)
{
	int		result;
	char	*temp;
	char	**element;

	if (ft_isemptyline(line))
		return (1);
	temp = ft_strtrim(line, WHITE_SPACE);
	element = ft_extract_element(temp);
	free(temp);
	temp = ft_strtrim(element[1], WHITE_SPACE);
	result = element[0] != NULL && ft_check_valid_file_elements(element[0]) &&
		ft_check_resolution(element[0], temp, &game_file->resolution) &&
		ft_check_north_path(element[0], temp, &game_file->no_path) &&
		ft_check_south_path(element[0], temp, &game_file->so_path) &&
		ft_check_east_path(element[0], temp, &game_file->ea_path) &&
		ft_check_west_path(element[0], temp, &game_file->we_path) &&
		ft_check_sprite_path(element[0], temp, &game_file->sprite_path) &&
		ft_check_ceiling(element[0], temp, &game_file->ceiling) &&
		ft_check_floor(element[0], temp, &game_file->floor);
	free(temp);
	ft_free_array(element);
	return (result);
}

int			ft_check_valid_file_elements(char *header)
{
	if (!header || ft_strcmp(header, "C") == 0 ||
		ft_strcmp(header, "F") == 0 ||
		ft_strcmp(header, "R") == 0 ||
		ft_strcmp(header, "NO") == 0 ||
		ft_strcmp(header, "SO") == 0 ||
		ft_strcmp(header, "WE") == 0 ||
		ft_strcmp(header, "EA") == 0 ||
		ft_strcmp(header, "S") == 0)
		return (1);
	return (ft_put_error("Missing or invalid element"));
}

char		**ft_extract_element(char *line)
{
	int i;
	int len;
	char **elements;

	i = 0;
	len = ft_strlen(line);
	while (line[i] != ' ')
		i++;
	
	elements = (char **)malloc(sizeof(char *) *  3);
	if (!elements)
		return (NULL);
	elements[0] = ft_substr(line, 0, i);
	elements[1] = ft_substr(line, i, len);
	elements[2] = NULL;

	return(elements);
}
