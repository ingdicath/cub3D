/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_orientacion.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:45:18 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/25 17:02:01 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int				ft_set_sprites_and_orientation(t_map *map)
{
	int			i;
	int			j;
	int			k;

	ft_memory_space_sprites(map);
	k = 0;
	i = 0;
	while (map->matrix[i] != NULL)
	{
		j = 0;
		while (map->matrix[i][j] != '\0')
		{
			if (!ft_check_unique_orientation(map, i, j))
				return (0);
			else if (ft_calc_sprite_variables(map, i, j, k))
				k++;
			j++;
		}
		i++;
	}
	// print_array	(map->sprites, map->num_sprites); // borrar
	if (map->orientation == '\0')
		return (ft_put_error("check orientation in the map"));
	return (1);
}

int				ft_memory_space_sprites(t_map *map)
{
	t_sprite	*sprites;

	sprites = (t_sprite *)malloc(sizeof(t_sprite) * map->num_sprites); //LIBERA
	if (sprites == NULL)
		return (0);
	map->sprites = sprites;
	return (1);
}

int				ft_calc_sprite_variables(t_map *map, int i, int j, int k)
{
	if (map->matrix[i][j] == '2')
	{
		map->sprites[k].position.x = j + 0.5;
		map->sprites[k].position.y = i + 0.5;
		map->sprites[k].distance = 0;
		return (1);
	}
	return (0);
}

/*
** map->start_pos.x = j and map->start_pos.y = i,  it was changed to simulate
** the coordinates of a Cartesian plane.
** map->matrix[i][j] = '0', changed to '0' to make the cell walkable
*/

int				ft_check_unique_orientation(t_map *map, int i, int j)
{
	if (map->matrix[i][j] == 'N' || map->matrix[i][j] == 'S' ||
		map->matrix[i][j] == 'W' || map->matrix[i][j] == 'E')
	{
		if (map->orientation != '\0')
			return (0);
		map->orientation = map->matrix[i][j];
		map->start_pos.x = j;
		map->start_pos.y = i;
		map->matrix[i][j] = '0';
	}
	return (1);
}

// borrar
void			print_array(t_sprite *sprites, int x)
{
	while (x > 0)
	{
		printf("pos x%f , pos y%f , distance %f \n", sprites->position.x, sprites->position.y, sprites->distance);
		sprites++;
		x--;
	}
}
