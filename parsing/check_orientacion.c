#include "../cub3d.h"

// static void prueba ( t_sprite  *sprite, int i , int j){
// 		printf("hola %d %d\n", i , j );
// t_sprite *sprites;
	
// 	sprites = (t_sprite *)malloc(sizeof(t_sprite) * map->num_sprites); // LIBERAR!!!
// 	if (sprites == NULL)
// 		return(0);
// 	map->sprite = sprites;

static int  prueba(t_map  *map, int i , int j, int k)
{
	if (map->matrix[i][j] == '2')
	{
		map->sprites[k].position.x = j + 0.5;
		map->sprites[k].position.y = i + 0.5;
		map->sprites[k].distance = 0;
		return(1);
	}
	return (0);
}

static int nose(t_map *map){

	t_sprite *sprites;
	
	sprites = (t_sprite *)malloc(sizeof(t_sprite) * map->num_sprites); // LIBERAR!!!
	if (sprites == NULL)
		return(0);
	map->sprites = sprites;
	return(1);
}
		

int		ft_set_sprites_and_orientation(t_map *map)
{
	int i;
	int j;
	int k;
	
	nose(map);
	k = 0;
	i = 0;
	while (map->matrix[i] != NULL)
	{
		j = 0;
		while (map->matrix[i][j] != '\0')
		{
			if (!ft_check_unique_orientation(map, i, j))
				return (0);
			else if (prueba(map, i, j, k))
				k++;
			j++;
		}
		i++;
	}
	// print_array	(map->sprites, map->num_sprites); // borrar
	if (map->orientation == '\0')
		return (0);
	return (1);
}

int		ft_check_unique_orientation(t_map *map, int i, int j)
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
	return(1);
}

// borrar
void 			print_array(t_sprite *sprites, int x)
{
	while (x>0){

		printf("pos x%f , pos y%f , distance %f \n", sprites->position.x,sprites->position.y , sprites->distance );
		sprites++;
		x--;
	}
}