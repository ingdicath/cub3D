/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:53:13 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/28 10:29:53 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void			ft_sort_sprites(t_map *map, t_position current_pos)
{
	int			i;
	int			j;
	t_sprite	temp;

	i = 0;
	ft_calc_dist_sprite(map, current_pos);
	while (i < map->num_sprites)
	{
		j = i + 1;
		while (j < map->num_sprites)
		{
			if (map->sprites[i].distance < map->sprites[j].distance)
			{
				temp = map->sprites[i];
				map->sprites[i] = map->sprites[j];
				map->sprites[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void			ft_calc_dist_sprite(t_map *map, t_position current_pos)
{
	int			i;
	t_position	relative;

	i = 0;
	while (i < map->num_sprites)
	{
		relative.x = current_pos.x - map->sprites[i].position.x;
		relative.y = current_pos.y - map->sprites[i].position.y;
		map->sprites[i].distance = relative.x * relative.x + relative.y *
			relative.y;
		i++;
	}
}

int				ft_count_sprite_types(t_map *map, char **sprite_path)
{
	int			i;
	int			type;

	i = 0;
	while (i < map->num_sprites)
	{
		type = map->sprites[i].type;
		map->type_sprite[type] = 1;
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (map->type_sprite[i])
			map->num_type_sprite++;
		i++;
	}
	if (ft_array_size(sprite_path) != map->num_type_sprite)
		return (ft_put_error("Sprite textures do not match"));
	return (1);
}

int				ft_check_additional_sprites(char *line)
{
	int			i;
	int			res;
	char		*temp;

	if (ft_isemptyline(line))
		return (0);
	temp = ft_strtrim(line, WHITE_SPACE);
	i = 0;
	res = 0;
	if (temp[i] == 'S' && (ft_check_extension(temp, XPM) ||
		ft_check_extension(temp, PNG)))
		res = 1;
	free(temp);
	return (res);
}

int				ft_validate_additional_sprites(char *line,
					t_game_file *game_file)
{
	int			result;
	char		*temp;
	char		**element;

	temp = ft_strtrim(line, WHITE_SPACE);
	element = ft_extract_element(temp);
	free(temp);
	temp = ft_strtrim(element[1], WHITE_SPACE);
	result = ft_check_sprite_path(element[0], temp, &game_file->sprite_path);
	free(temp);
	ft_free_array(element);
	return (result);
}
