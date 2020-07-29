/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/22 13:15:55 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/07/28 21:40:14 by dsalaman      ########   odam.nl         */
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

int ft_check_valid_char(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != '2' &&
			line[i] != ' ' && line[i] != 'N' && line[i] != 'S' &&
			line[i] != 'W' && line[i] != 'E')
			return (ft_put_error("invalid character in the map"));
		i++;
	}
	return (1);
}

void	ft_reset_input(t_input *mapfile)
{
	mapfile->ceiling.red = -1;
	mapfile->ceiling.green = -1;
	mapfile->ceiling.blue = -1;
	mapfile->floor.red = -1;
	mapfile->floor.green = -1;
	mapfile->floor.blue = -1;
	mapfile->resolution.width = -1;
	mapfile->resolution.height = -1;
	mapfile->no_texture = NULL;
	mapfile->so_texture = NULL;
	mapfile->ea_texture = NULL;
	mapfile->we_texture = NULL;
	mapfile->sprite = NULL;
	mapfile->map = NULL;
	mapfile->start_pos_x = -1;
	mapfile->start_pos_y = -1;
}

int		ft_check_complete_elements(t_input *mapfile)
{
	if (mapfile->ceiling.red == -1 || mapfile->ceiling.green == -1 ||
		mapfile->ceiling.blue == -1 || mapfile->floor.red == -1 ||
		mapfile->floor.green == -1 || mapfile->floor.blue == -1 ||
		mapfile->resolution.width == -1 || mapfile->resolution.height == -1 ||
		mapfile->no_texture == NULL || mapfile->so_texture == NULL ||
		mapfile->ea_texture == NULL || mapfile->we_texture == NULL ||
		mapfile->sprite == NULL)
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

int			ft_read_file_map(char *file_name, t_input *mapfile)
{
	int		ret;
	int		fd;
	char	*line;
	char	*join_lines;//new
	char	**line_split;
	int		length;//new

	length = 0;//new
	ret = 1;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (ft_put_error("cannot open .cub map file"));
	length = ft_strlen(line);//new
	join_line = malloc(sizeof)(char) * (length + 1);//new


	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret < 0)
			return (ft_put_error("file not found"));
		if (ft_check_complete_elements(mapfile))
		{
			if (ft_isemptyline(line) && mapfile->map == NULL)
				continue ;
			// ft_join_lines(file_name, mapfile);///// REVISAR FUNCION
			ft_fill_map(line, mapfile);///
			print_map(mapfile->map);
		}
		else
		{
			line_split = ft_split(line, ' ');
			ft_fill_elements(line_split, mapfile);
		}
		printfs(mapfile);

/*
        i = 0;
        while (i < ft_count_words(line, ' '))
        {
			ft_putstr(line_split[i]);
      		ft_putstr(",");
			i++;
		}
*/
		free(line);
		printf("\n");
	}
	close(fd);
	return (0);
}

int			ft_fill_elements(char **line_split, t_input *mapfile)
{
	int		result;

	result = ft_check_resolution(line_split, &mapfile->resolution);
	result = ft_check_ceiling(line_split, &mapfile->ceiling);
	result = ft_check_floor(line_split, &mapfile->floor);
	result = ft_check_north_texture(line_split, &mapfile->no_texture);
	result = ft_check_south_texture(line_split, &mapfile->so_texture);
	result = ft_check_east_texture(line_split, &mapfile->ea_texture);
	result = ft_check_west_texture(line_split, &mapfile->we_texture);
	result = ft_check_sprite_texture(line_split, &mapfile->sprite);
	return (result);
}

char		*ft_join_lines(char *line)
{
	int		ret;
	int		fd;
	char	*new_line;
	int		length;

	length = 0;
	ret = 1;
	while (ret > 0)
	{
		new_line = malloc(sizeof(char) * (length+ 1));
		if (new_line == 0)
		{
			free(new_line);
			return (NULL);
		}
		ret = read(fd, new_line, length);
		if (ret < 0)
		{
			free(new_line);
			return (NULL);
		}
		return (line);
	}

}


int			ft_fill_map(char *line, t_input *mapfile)
{
	int		i;
	int		join_lines;

	i = 0;
	if (ft_check_valid_char(line))
	{
		printf("pollo malo %s\n",line);//borrar
		*mapfile->map = ft_strdup(line);
		printf("pollooooooo %s\n",line);//borrar
		mapfile->map++;
		printf("hambreeee %s\n",line);//borrar
	}
	return (0);
}

void printfs(t_input *mapfile)
{
	printf("%d %d\n",mapfile->resolution.width,mapfile->resolution.height); //borrar
	printf("%d %d %d\n",mapfile->ceiling.red,mapfile->ceiling.green, mapfile->ceiling.blue); //borrar
	printf("%d %d %d\n",mapfile->floor.red,mapfile->floor.green, mapfile->floor.blue); //borrar
	printf("%s\n", mapfile->no_texture); //borrar
	printf("%s\n", mapfile->so_texture); //borrar
	printf("%s\n", mapfile->ea_texture); //borrar
	printf("%s\n", mapfile->we_texture); //borrar
	printf("%s\n", mapfile->sprite); //borrar
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

// 		if (line[i][j] == 'N' || line[i][j] == 'S' || line[i][j] == 'E' ||
// 			line[i][j] == 'W')
// 		{
// 			if (map->start_pos_x == -1 && map->start_pos_y == -1)


	// 	if (line[i][j] != 1)
	// 		return (ft_put_error("invalid character in the map"));

	// }


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
	return (0);
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
	return (0);
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
	return (0);
}

int		ft_check_north_texture(char **line, char **north_path)
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
	return (0);
}

int		ft_check_south_texture(char **line, char **south_path)
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
	return (0);
}

int		ft_check_west_texture(char **line, char **west_path)
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
	return (0);
}

int		ft_check_east_texture(char **line, char **east_path)
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
	return (0);
}

int		ft_check_sprite_texture(char **line, char **sprite_path)
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
	return (0);
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

int			main(int argc, char **argv)
{
	int		screenshot;
	int		error;
	t_input	file_map;
	int		result;

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
				screenshot = 1;
			else
			{
				ft_put_error("wrong argument for screenshot");
				error++;
			}
		}
	}
	if (error > 0)
		return (0);
	ft_reset_input(&file_map);
	result = ft_read_file_map(argv[1], &file_map);
	if (result == -1)
		return (-1);
	if (!ft_check_complete_elements(&file_map))
		return (ft_put_error("Scene map incomplete. Complete to continue"));
	// if (file_map == NULL)
	// 	return (-1);

	return (0);
}
/*
$ gcc parsing.c ft_split.c gnl/get_next_line.c cub3d_utils.c -fsanitize=address

solo puede existir un elemento de cada tipo:  una sola R, una sola C, F, etc..

para los colores se podria usar unsigned char, ya que su rango es de 0 - 255
*/
