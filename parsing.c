/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/22 13:15:55 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/07 11:36:34 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int			ft_check_extension(char *file_name, char *valid_ext)
{
	int		name_size;
	int		ext_size;
	char	*temp;

	name_size = ft_strlen(file_name);
	ext_size = ft_strlen(valid_ext);
	temp = ft_substr(file_name, (name_size - ext_size), name_size);
	if (ft_strcmp(temp, valid_ext) == 0)
		return (1);
	return (0);
}

int		ft_check_valid_char(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != '2' &&
			line[i] != ' ' && line[i] != 'N' && line[i] != 'S' &&
			line[i] != 'W' && line[i] != 'E')
			return (0);
		i++;
	}
	return (1);
}

int		ft_check_unique_orientation(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (map->data[i] != NULL)
	{
		j = 0;
		while (map->data[i][j] != '\0')
		{
			if (map->data[i][j] == 'N' || map->data[i][j] == 'S' ||
				map->data[i][j] == 'W' || map->data[i][j] == 'E')
			{
				if (map->orientation != '\0')
					return (0);
				map->orientation = map->data[i][j];
				map->start_pos.row = i;
				map->start_pos.column = j;
			}
			j++;
		}
		i++;
	}
	if (map->orientation == '\0')
		return (0);
	return (1);
}

void	ft_reset_input(t_game_file *game_file)
{
	game_file->ceiling.red = -1;
	game_file->ceiling.green = -1;
	game_file->ceiling.blue = -1;
	game_file->floor.red = -1;
	game_file->floor.green = -1;
	game_file->floor.blue = -1;
	game_file->resolution.width = -1;
	game_file->resolution.height = -1;
	game_file->no_path = NULL;
	game_file->so_path = NULL;
	game_file->ea_path = NULL;
	game_file->we_path = NULL;
	game_file->sprite_path = NULL;
	game_file->map.data = NULL;
	game_file->map.orientation = '\0';
	game_file->map.start_pos.row = -1;
	game_file->map.start_pos.column = -1;
}

int		ft_check_complete_elements(t_game_file *game_file)
{
	if (game_file->ceiling.red == -1 || game_file->ceiling.green == -1 ||
		game_file->ceiling.blue == -1 || game_file->floor.red == -1 ||
		game_file->floor.green == -1 || game_file->floor.blue == -1 ||
		game_file->resolution.width == -1 || game_file->resolution.height == -1 ||
		game_file->no_path == NULL || game_file->so_path == NULL ||
		game_file->ea_path == NULL || game_file->we_path == NULL ||
		game_file->sprite_path == NULL)
		return (0);
	else
		return (1);
}

int		ft_array_size(char **array)
{
	int i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int			ft_check_valid_color(char *color)
{
	int		len;
	char	*temp;

	len = ft_strlen(color);
	temp = ft_substr(color, 0, len - 1);
	if (color[len - 1] == ',' && ft_isnumber(temp))
		return (1);
	return (0);
}

int			ft_read_file(char *file_name, t_game_file *game_file)
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
		if (ft_check_complete_elements(game_file))
		{
			if (ft_isemptyline(line) && game_file->map.data == NULL)
				continue ;
			if (!ft_check_valid_char(line))
				return (ft_put_error("invalid character in the map"));
			game_file->map.data = ft_join_lines(game_file->map.data, line);
			//print_map(game_file->map.data);//borrar
		}
		else
		{
			line_split = ft_split(line, ' ');
			if (!ft_fill_elements(line_split, game_file))
			{
				free(line);
				return (ft_put_error("check map elements"));
			}
		}
		// printfs(game_file);//borrar

/*
        i = 0;
        while (i < ft_count_words(line, ' '))
        {
			ft_putstr(line_split[i]);
      		ft_putstr(",");
			i++;
		}
*/
		
		// AQUIIIIIIIIIIIII HAYYYYY UNN LEEEEEAAAAAAKKKKKKK, FALTA LIBERAR EN LOS RETURNS
		free(line);
		printf("\n");
	}
	close(fd);
	return (1);
}

int			ft_fill_elements(char **line_split, t_game_file *game_file)
{
	int		result;

	result = 1;
	result = ft_check_resolution(line_split, &game_file->resolution)
	&& ft_check_ceiling(line_split, &game_file->ceiling)
	&& ft_check_floor(line_split, &game_file->floor)
	&& ft_check_north_path(line_split, &game_file->no_path)
	&& ft_check_south_path(line_split, &game_file->so_path)
	&& ft_check_east_path(line_split, &game_file->ea_path)
	&& ft_check_west_path(line_split, &game_file->we_path)
	&& ft_check_sprite_path(line_split, &game_file->sprite_path);
	printf("result is: %d\n", result);
	return (result);
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

void printfs(t_game_file *game_file)
{
	printf("%d %d\n",game_file->resolution.width,game_file->resolution.height); //borrar
	printf("%d %d %d\n",game_file->ceiling.red,game_file->ceiling.green, game_file->ceiling.blue); //borrar
	printf("%d %d %d\n",game_file->floor.red,game_file->floor.green, game_file->floor.blue); //borrar
	printf("%s\n", game_file->no_path); //borrar
	printf("%s\n", game_file->so_path); //borrar
	printf("%s\n", game_file->ea_path); //borrar
	printf("%s\n", game_file->we_path); //borrar
	printf("%s\n", game_file->sprite_path); //borrar
	print_map(game_file->map.data);
}

void print_map(char **map)
{
	int i = 0;
	while (map[i] != NULL)
	{
		printf("mapa %s\n",map[i]);
		i++;
	}
}

int		ft_check_resolution(char **line, t_screen *resolution)
{
	// int	i;

	// i = 0;
	// while (line[i])
	// {
	// 	printf("helo %d %s\n", i, line[i]);
	// 	i++;
	// }
	if (line[0] && (ft_strcmp(line[0], "R") == 0))
	{
		if (resolution->width >= 0 || resolution->height >= 0)
			return (ft_put_error("argument(s) for RES already exist(s)"));
		if (ft_array_size(line) != 3)
			return (ft_put_error("wrong number of arguments for RES"));
		if (!ft_isnumber(line[1]) || !ft_isnumber(line[2]))
			return (ft_put_error("is not number for resolution"));
		resolution->width = ft_atoi(line[1]);
		resolution->height = ft_atoi(line[2]);
		printf("ancho %d \n", resolution->width); // borrar
		printf("altura %d \n", resolution->height); //borrar
		if (resolution->width <= 0 || resolution->height <= 0)
			return (ft_put_error("Resolution must be greater than 0"));
	}
/*
	printf ("%d\n", resolution.width);
	//borrar prueba
	while (line[i])
    {
		printf ("%s\n", line[i]);
		i++;
	}
	printf("\n");
*/
	return (1);
}

int		ft_check_ceiling(char **line, t_color *ceiling)
{
	if (line[0] && (ft_strcmp(line[0], "C") == 0))
	{
		if (ceiling->red >= 0 || ceiling->green >= 0 || ceiling->blue >= 0)
			return (ft_put_error("argument(s) already for ceiling exist(s)"));
		if (line[4])
			return (ft_put_error("more arguments for ceiling than expected."));
		if (!line[1] || !line[2] || !line[3])
			return (ft_put_error("invalid arguments"));
		if (!ft_check_valid_color(line[1]) || !ft_check_valid_color(line[2])
			|| !ft_isnumber(line[3]))
			return (ft_put_error("Some of this arguments are not numbers"));
		ceiling->red = atoi(line[1]);
		ceiling->green = atoi(line[2]);
		ceiling->blue = atoi(line[3]);
		printf("red ceiling %d \n", ceiling->red); // borrar
		printf("blue ceiling %d \n", ceiling->green); //borrar
		printf("green ceiling %d \n", ceiling->blue); //borrar
		if (ceiling->red < 0 || ceiling->green < 0 || ceiling->blue < 0)
			return (ft_put_error("Non negative numbers are expected"));
		if (ceiling->red > 255 || ceiling->green > 255 || ceiling->blue > 255)
			return (ft_put_error("Color value(s) must be maximum 255"));
	}
	return (1);
}

int		ft_check_floor(char **line, t_color *floor)
{
	if (line[0] && (ft_strcmp(line[0], "F") == 0))
	{
		if (floor->red >= 0 || floor->green >= 0 || floor->blue >= 0)
			return (ft_put_error("argument(s) already for floor exist(s)"));
		if (line[4])
			return (ft_put_error("more arguments for floor than expected"));
		if (!line[1] || !line[2] || !line[3])
			return (ft_put_error("invalid arguments"));
		if (!ft_check_valid_color(line[1]) || !ft_check_valid_color(line[2])
			|| !ft_isnumber(line[3]))
			return (ft_put_error("Some of this arguments are not numbers"));
		floor->red = atoi(line[1]);
		floor->green = atoi(line[2]);
		floor->blue = atoi(line[3]);
		printf("red floor %d \n", floor->red); // borrar
		printf("blue floor %d \n", floor->green); //borrar
		printf("green floor %d \n", floor->blue); //borrar
		if (floor->red < 0 || floor->green < 0 || floor->blue < 0)
			return (ft_put_error("Non negative numbers are expected"));
		if (floor->red > 255 || floor->green > 255 || floor->blue > 255)
			return (ft_put_error("Color value(s) must be maximum 255"));
	}
	return (1);
}

int		ft_check_north_path(char **line, char **north_path)
{
	if (line[0] && (ft_strcmp(line[0], "NO") == 0))
	{
		if (*north_path != NULL)
			return (ft_put_error("argument(s) already for NO exist(s)"));
		if (line[2])
			return (ft_put_error("more arguments than expected for NO text."));
		if (!line[1])
			return (ft_put_error("invalid arguments for NO texture"));
		if (ft_check_path(line[1]))
			*north_path = line[1];
		printf("north texture %s\n", *north_path); // borrar
	}
	return (1);
}

int		ft_check_south_path(char **line, char **south_path)
{
	if (line[0] && (ft_strcmp(line[0], "SO") == 0))
	{
		if (*south_path != NULL)
			return (ft_put_error("argument(s) already for SO exist(s)"));
		if (line[2])
			return (ft_put_error("more arguments than expected for SO text."));
		if (!line[1])
			return (ft_put_error("invalid arguments for SO texture"));
		if (ft_check_path(line[1]))
			*south_path = line[1];
		printf("south texture %s\n", *south_path); // borrar
	}
	return (1);
}

int		ft_check_west_path(char **line, char **west_path)
{
	if (line[0] && (ft_strcmp(line[0], "WE") == 0))
	{
		if (*west_path != NULL)
			return (ft_put_error("argument(s) already for WE exist(s)"));
		if (line[2])
			return (ft_put_error("more arguments than expected for WE text."));
		if (!line[1])
			return (ft_put_error("invalid arguments WE texture"));
		if (ft_check_path(line[1]))
			*west_path = line[1];
		printf("west texture %s\n", *west_path); // borrar
	}
	return (1);
}

int		ft_check_east_path(char **line, char **east_path)
{
	if (line[0] && (ft_strcmp(line[0], "EA") == 0))
	{
		if (*east_path != NULL)
			return (ft_put_error("argument(s) already for EA exist(s)"));
		if (line[2])
			return (ft_put_error("more arguments than expected for EA text."));
		if (!line[1])
			return (ft_put_error("invalid arguments for EA texture"));
		if (ft_check_path(line[1]))
			*east_path = line[1];
		printf("east texture %s\n", *east_path); // borrar
	}
	return (1);
}

int		ft_check_sprite_path(char **line, char **sprite_path)
{
	if (line[0] && (ft_strcmp(line[0], "S") == 0))
	{
		if (*sprite_path != NULL)
			return (ft_put_error("argument(s) already for sprite exist(s)"));
		if (line[2])
			return (ft_put_error("more arguments than expected for texture"));
		if (!line[1])
			return (ft_put_error("invalid arguments for sprite texture"));
		if (ft_check_path(line[1]))
			*sprite_path = line[1];
		printf("sprite texture %s\n", *sprite_path); // borrar
	}
	return (1);
}

int		ft_check_path(char *str)
{
	int		ret;
	int		i;

	i = 0;
	if (str[i] != '.')
		return (ft_put_error("invalid path"));
	if (!ft_check_extension(str, XPM) && !ft_check_extension(str, PNG))
		return (ft_put_error("invalid extension for texture"));
	ret = open(str, O_RDONLY);
	printf("valor: %d\n", ret);
	if (ret < 0)
		return (ft_put_error("file does not exist."));
	close(ret);
	return (1);
}

int 	ft_check_args(int argc, char **argv, int *screenshot)
{
	int		error;

	*screenshot = 0;
	error = 0;
	if (argc < 2)
		return (ft_put_error("at least one argument was expected"));
	if (argc > 3)
		return (ft_put_error("too many arguments"));
	if (argc >= 2)
	{
		if (!ft_check_extension(argv[1], CUB))
		{
			ft_put_error("wrong extension in map file");
			error++;
		}
		if (argc == 3)
		{
			if (ft_strcmp(argv[2], "--save") == 0)
				*screenshot = 1;
			else
			{
				ft_put_error("wrong argument for screenshot");
				error++;
			}
		}
	}
	if (error > 0)
		return (0);
	return(1);
}


int			main(int argc, char **argv)
{
	int			screenshot;
	t_game_file	game_file;

		// chequeo de input
	
	if (!ft_check_args(argc, argv, &screenshot))
		return(0);

	ft_reset_input(&game_file);
	
	if (!ft_read_file(argv[1], &game_file))
		return (0);
	if (!ft_check_complete_elements(&game_file))
		return (ft_put_error("Scene map incomplete. Complete to continue"));
	if (!ft_check_unique_orientation(&game_file.map))
		return (ft_put_error("check orientation in the map"));
	
	printfs(&game_file);

	if(screenshot)
		ft_save_screen(game_file);
	else
		ft_start_game(game_file);


	return (0);
}
/*
$ gcc parsing.c ft_split.c gnl/get_next_line.c cub3d_utils.c start_game.c -fsanitize=address
gcc parsing.c ft_split.c gnl/get_next_line.c cub3d_utils.c start_game.c -Lmlx -lmlx -framework OpenGL -framework AppKit
gcc -Wall -Werror -Wextra parsing.c ft_split.c gnl/get_next_line.c cub3d_utils.c -fsanitize=address

solo puede existir un elemento de cada tipo:  una sola R, una sola C, F, etc..

para los colores se podria usar unsigned char, ya que su rango es de 0 - 255
se podria poner una condicion para que solo acepte espacios
*/
