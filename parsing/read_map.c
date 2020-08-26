/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:48:45 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/26 13:50:47 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			ft_read_file(char *file_name, t_game_file *file)
{
	int		ret;
	int		fd;
	int		valid;
	char	*line;

	valid = 1;
	ret = 1;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (ft_put_error("cannot open .cub map file"));
	while (ret > 0 && valid)
	{
		ret = get_next_line(fd, &line);

		// printf("valor ret %d\n", ret);

		if (ret < 0)
			return (ft_put_error("file not found"));
		if (!ft_read_line(file, line))
			valid = 0;
		free(line);
	}
	close(fd);
	return (valid);
}

int			ft_read_line(t_game_file *file, char *line)
{
	char	**line_split;

	if (ft_check_complete_elements(file))
	{
		if (ft_isemptyline(line) && file->map.matrix == NULL)
			return (1);
		if (!ft_count_sprites(line, &file->map))
			return (ft_put_error("invalid character in the map"));
		file->map.matrix = ft_join_lines(file->map.matrix, line);
	}
	else
	{
		line_split = ft_split(line, ' ');
		if (!ft_fill_elements(line_split, file))
			return (ft_put_error("check map elements"));
	}
	return (1);
}

int			ft_check_complete_elements(t_game_file *game_file)
{
	if (game_file->ceiling.red == -1 || game_file->ceiling.green == -1 ||
		game_file->ceiling.blue == -1 || game_file->floor.red == -1 ||
		game_file->floor.green == -1 || game_file->floor.blue == -1 ||
		game_file->resolution.width == -1 ||
		game_file->resolution.height == -1 || game_file->no_path == NULL ||
		game_file->so_path == NULL || game_file->ea_path == NULL ||
		game_file->we_path == NULL || game_file->sprite_path == NULL)
		return (0);
	else
		return (1);
}

int			ft_count_sprites(char *line, t_map *map)
{
	int		i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!ft_check_valid_char(line[i]))
			return (0);
		else if (line[i] == '2')
			map->num_sprites++;
		i++;
	}
	return (1);
}

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
}
