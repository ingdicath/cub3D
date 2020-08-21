#include "cub3d.h"
#include <stdio.h> //borrar

// ARREGLAR TIENE 26 LINEAS

int		ft_check_unique_orientation(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (map->matrix[i] != NULL)
	{
		j = 0;
		while (map->matrix[i][j] != '\0')
		{
			if (map->matrix[i][j] == 'N' || map->matrix[i][j] == 'S' ||
				map->matrix[i][j] == 'W' || map->matrix[i][j] == 'E')
			{
				if (map->orientation != '\0')
					return (0);
				map->orientation = map->matrix[i][j];
				map->start_pos.x = j;  //se cambio para simular las coordenadas de un plano cartesiano
				map->start_pos.y = i;
				map->matrix[i][j] = '0'; // se cambio a 0 para hacer la celda caminable
			}
			j++;
		}
		i++;
	}
	if (map->orientation == '\0')
		return (0);
	return (1);
}
