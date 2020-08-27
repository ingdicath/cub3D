/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:53:13 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/27 17:23:13 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void			ft_sort_sprites(t_map *map, t_position current_pos)
{
	int			i;
	t_sprite	temp;

	i = 0;
	ft_calc_dist_sprite(map, current_pos);
	while (i < map->num_sprites)
	{
		if (map->sprites[i].distance < map->sprites[i + 1].distance)
		{
			temp = map->sprites[i];
			map->sprites[i] = map->sprites[i + 1];
			map->sprites[i + 1] = temp;
			i = 0;
		}
		else
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
		map->sprites[i].distance = relative.x * relative.x + relative.y * relative.y;
		i++;
	}
}
