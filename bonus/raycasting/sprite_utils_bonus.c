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
