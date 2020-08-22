#include "../cub3d.h"

char		**ft_join_lines(char **matrix, char *new_line)
{
	int		rows;
	char	**new_matrix;

	rows = 0;
	while (matrix != NULL && matrix[rows])
		rows++;
	new_matrix = (char **)malloc(sizeof(char *) * (rows + 2));
	if (!new_matrix)
		return (NULL);
	rows = 0;
	while (matrix != NULL && matrix[rows])
	{
		new_matrix[rows] = matrix[rows];
		rows++;
	}
	new_matrix[rows] = ft_strdup(new_line);
	rows++;
	new_matrix[rows] = NULL;
	return (new_matrix);
	// toca hacer free de la matrix
}

// int		ft_check_valid_char(char *line, t_map *map)
// {
// 	int i;

// 	i = 0;
// 	while (line[i] != '\0')
// 	{
// 		if (line[i] != '0' && line[i] != '1' && line[i] != '2' &&
// 			line[i] != ' ' && line[i] != 'N' && line[i] != 'S' &&
// 			line[i] != 'W' && line[i] != 'E')
// 			return (0);
// 		else if (line[i] == '2')
// 			map->num_sprites++;
// 		i++;
// 	}
// 	return (1);
// }

int		ft_check_valid_char(char c)
{
	if (c != '0' && c != '1' && c != '2' &&
			c != ' ' && c != 'N' && c != 'S' &&
			c != 'W' && c != 'E')
			return (0);
	
	return (1);
}

int		ft_count_sprites(char *line, t_map *map)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if(!ft_check_valid_char(line[i]))
			return (0);
		else if (line[i] == '2')
			map->num_sprites++;
		i++;
	}
	return (1);
}

int		ft_check_complete_elements(t_game_file *game_file)
{
	if (game_file->ceiling.red == -1 || game_file->ceiling.green == -1 ||
		game_file->ceiling.blue == -1 || game_file->floor.red == -1 ||
		game_file->floor.green == -1 || game_file->floor.blue == -1 ||
		game_file->win_size.width == -1 ||
		game_file->win_size.height == -1 || game_file->no_path == NULL ||
		game_file->so_path == NULL || game_file->ea_path == NULL ||
		game_file->we_path == NULL || game_file->sprite_path == NULL)
		return (0);
	else
		return (1);
}

int			ft_read_file(char *file_name, t_game_file *file)
{
	int		ret;
	int		fd;
	char	*line;
	char	**line_split;

	ret = 1;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (ft_put_error("cannot open .cub map file"));
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret < 0)
			return (ft_put_error("file not found"));
		if (ft_check_complete_elements(file))
		{
			if (ft_isemptyline(line) && file->map.matrix == NULL)
				continue ;
			if (!ft_count_sprites(line, &file->map))
				return (ft_put_error("invalid character in the map"));
			file->map.matrix = ft_join_lines(file->map.matrix, line);
		}
		else
		{
			line_split = ft_split(line, ' ');
			if (!ft_fill_elements(line_split, file))
			{
				free(line);
				return (ft_put_error("check map elements"));
			}
		}
		// AQUIIIIIIIIIIIII HAYYYYY UNN LEaKKKKKK, FALTA LIBERAR EN LOS RETURNS
		free(line);
	}
	close(fd);
	return (1);
}


//TOCAR PARTIR LA FUNCION READ FILE EN DOS