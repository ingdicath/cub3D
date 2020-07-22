/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/22 13:15:55 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/07/22 13:16:34 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int		ft_check_file_type(char *map_name)
{
	int i;

	i = ft_strlen(map_name);
	if (map_name[i - 4] == '.' && map_name[i - 3] == 'c'
		&& map_name[i - 2] == 'u' && map_name[i - 1] == 'b')
		return (1);
	return (-1);
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
}

int		ft_check_final_elements(t_input *mapfile)
{
	if (mapfile->ceiling.red == -1 || mapfile->ceiling.green == -1 ||
		mapfile->ceiling.blue == -1 || mapfile->floor.red == -1 ||
		mapfile->floor.green == -1 || mapfile->floor.blue == -1 ||
		mapfile->resolution.width == -1 || mapfile->resolution.height == -1 ||
		mapfile->no_texture == NULL || mapfile->so_texture == NULL ||
		mapfile->ea_texture == NULL || mapfile->we_texture == NULL ||
		mapfile->sprite == NULL)
		return (ft_put_error("some elements are missing. Check again"));
	else
		return (0);
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
	int		i;
	int		result;
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
		line_split = ft_split(line,' ');
		result = ft_check_resolution(line_split, &mapfile->resolution);
		printf("%d %d\n",mapfile->resolution.width,mapfile->resolution.height); //borrar
		result = ft_check_ceiling(line_split, &mapfile->ceiling);
		printf("%d %d %d\n",mapfile->ceiling.red,mapfile->ceiling.green, mapfile->ceiling.blue); //borrar
		result = ft_check_floor(line_split, &mapfile->floor);
		printf("%d %d %d\n",mapfile->floor.red,mapfile->floor.green, mapfile->floor.blue); //borrar
		result = ft_check_north_texture(line_split, &mapfile->no_texture);
		printf("%s\n", mapfile->no_texture); //borrar
		result = ft_check_south_texture(line_split, &mapfile->so_texture); // revisar, no se puso &mapfile
		printf("%s\n", mapfile->so_texture); //borrar
		result = ft_check_east_texture(line_split, &mapfile->ea_texture); // revisar, no se puso &mapfile
		printf("%s\n", mapfile->ea_texture); //borrar
		result = ft_check_west_texture(line_split, &mapfile->we_texture); // revisar, no se puso &mapfile
		printf("%s\n", mapfile->we_texture); //borrar
		result = ft_check_sprite_texture(line_split, &mapfile->sprite); // revisar, no se puso &mapfile
		printf("%s\n", mapfile->sprite); //borrar
/*
        i = 0;
        while (i < ft_count_words(line, ' '))
        {
			ft_putstr(line_split[i]);
      		ft_putstr(",");
			i++;
		}
*/
		ft_putstr("\n");
		free(line);
	}
	return (0);
}

int		ft_check_resolution(char **line, t_screen *resolution)
{
	if (line[0] && line[0][0] == 'R')
	{
		if (resolution->width >= 0 || resolution->height >= 0)
			return (ft_put_error("argument(s) for RES already exist(s)"));
		if (line[3])
			return (ft_put_error("more arguments than expected for RES"));
		if (!line[1] || !line[2])
			return (ft_put_error("invalid arguments for resolution"));
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
/*
	int i;
	i = 0;
	while(line[i])
	{
		printf("helo %d %s\n", i, line[i]);
		i++;
	}
*/
	if (line[0] && line[0][0] == 'C')
	{
		if (ceiling->red >= 0 || ceiling->green >= 0 || ceiling->blue >= 0)
			return (ft_put_error("argument(s) already for ceiling exist(s)"));
		if (line[4])
			return (ft_put_error("more arguments for ceiling than expected") &&
				ft_put_error("Comma ',' must to be next to the number"));
		if (!line[1] || !line[2] || !line[3])
			return (ft_put_error("invalid arguments"));
		if (!ft_check_valid_color(line[1]) || !ft_check_valid_color(line[2])
			|| !ft_isnumber(line[3]))
			return (ft_put_error("Some of this arguments are not numbers") &&
				ft_put_error("Comma ',' must to be next to the number"));
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
	if (line[0] && line[0][0] == 'F')
	{
		if (floor->red >= 0 || floor->green >= 0 || floor->blue >= 0)
			return (ft_put_error("argument(s) already for floor exist(s)"));
		if (line[4])
			return (ft_put_error("more arguments for floor than expected") &&
				ft_put_error("Comma ',' must to be next to the number"));
		if (!line[1] || !line[2] || !line[3])
			return (ft_put_error("invalid arguments"));
		if (!ft_check_valid_color(line[1]) || !ft_check_valid_color(line[2])
			|| !ft_isnumber(line[3]))
			return (ft_put_error("Some of this arguments are not numbers") &&
				ft_put_error("Comma ',' must to be next to the number"));
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
	if (line[0] && (ft_strncmp(line[0],"NO", 2) == 0))
	{
		if (*north_path != NULL)
			return (ft_put_error("argument(s) already for NO exist(s)"));
		if (line[2])
			return (ft_put_error("more arguments than expected for NO text."));
		if (!line[1])
			return (ft_put_error("invalid arguments for NO texture"));
		*north_path = line[1];
		printf("north texture %s\n", *north_path); // borrar
	}
	return (0);
}

int		ft_check_south_texture(char **line, char **south_path)
{
	if (line[0] && (ft_strncmp(line[0],"SO", 2) == 0))
	{
		if (*south_path != NULL)
			return (ft_put_error("argument(s) already for SO exist(s)"));
		if (line[2])
			return (ft_put_error("more arguments than expected for SO text."));
		if (!line[1])
			return (ft_put_error("invalid arguments for SO texture"));
		*south_path = line[1];
		printf("south texture %s\n", *south_path); // borrar
	}
	return (0);
}

int		ft_check_west_texture(char **line, char **west_path)
{
	if (line[0] && (ft_strncmp(line[0],"WE", 2) == 0))
	{
		if (*west_path != NULL)
			return (ft_put_error("argument(s) already for WE exist(s)"));
		if (line[2])
			return (ft_put_error("more arguments than expected for WE text."));
		if (!line[1])
			return (ft_put_error("invalid arguments WE texture"));
		*west_path = line[1];
		printf("west texture %s\n", *west_path); // borrar
	}
	return (0);
}

int		ft_check_east_texture(char **line, char **east_path)
{
	if (line[0] && (ft_strncmp(line[0],"EA", 2) == 0))
	{
		if (*east_path != NULL)
			return (ft_put_error("argument(s) already for EA exist(s)"));
		if (line[2])
			return (ft_put_error("more arguments than expected for EA text."));
		if (!line[1])
			return (ft_put_error("invalid arguments for EA texture"));
		*east_path = line[1];
		printf("east texture %s\n", *east_path); // borrar
	}
	return (0);
}

int		ft_check_sprite_texture(char **line, char **sprite_path)
{
	if (line[0] && (ft_strncmp(line[0],"S", 1) == 0) && line[0][1] == '\0')
	{
		if (*sprite_path != NULL)
			return (ft_put_error("argument(s) already for sprite exist(s)"));
		if (line[2])
			return (ft_put_error("more arguments than expected for texture"));
		if (!line[1])
			return (ft_put_error("invalid arguments for sprite texture"));
		*sprite_path = line[1];
		printf("sprite texture %s\n", *sprite_path); // borrar
	}
	return (0);
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
		if (ft_check_file_type(argv[1]) == -1)
		{
			ft_put_error("wrong extension in map file");
			error++;
		}
		if (argc == 3)
		{
			if (ft_strncmp(argv[2], "--save", ft_strlen("--save")) == 0)
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
	// file_map = ft_read_file_map(argv[1]);
	ft_reset_input(&file_map);
	result = ft_read_file_map(argv[1], &file_map);
	if (result == -1)
		return (-1);
	ft_check_final_elements(&file_map);
	// if (file_map == NULL)
	// 	return (-1);
	return (0);
}
/*
$ gcc parsing.c ft_split.c gnl/get_next_line.c cub3d_utils.c

solo puede existir un elemento de cada tipo:  una sola R, una sola C, F, etc..
south texture y sprite lo estan leyendo dos veces
para los colores se podria usar unsigned char, ya que su rango es de 0 - 255
22Jjul
- como hacer para imprimir line[1] cuando la funcion tiene doble *? Quiero saber que tiene el contenido de line int ft_check_north_texture(char **line, char **north_path)
esto antes de entrar al condicional if
- validar tambien si me hace falta un elemento genere error, como hacerlo?
*/