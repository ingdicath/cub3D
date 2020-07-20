/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 11:02:40 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/07/20 21:54:06 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int ft_check_file_type(char *map_name)
{
    int i;
    
    i = ft_strlen(map_name);
    if (map_name[i - 4] == '.' && map_name[i - 3] == 'c' 
    	&& map_name[i - 2] == 'u' && map_name[i - 1] == 'b')
            return (1);
    return(-1);
}

int ft_check_valid_color(char *color)
{
	int len;
	char *temp;

	len = ft_strlen(color);
	temp = ft_substr(color, 0, len-1);
	if (color[len-1] == ',' && ft_isnumber(temp))
		return (1);
	return (0);
}

int ft_read_file_map(char *file_name, t_input *mapfile)
{
    int 	ret;
    int 	fd;
    int		i;
    int		result;
    char 	*line;
  	char	**line_split;

    ret = 1;
    fd = open(file_name, O_RDONLY);	
    while (ret > 0)
    {
        ret = get_next_line(fd, &line);
        if (ret < 0)
      		return (ft_put_error("File not found"));
      	line_split = ft_split(line,' ');
     
       	result = ft_check_resolution(line_split, &mapfile->resolution); //borrar
       	printf("%d %d\n",mapfile->resolution.width,mapfile->resolution.height); //borrar
       	result = ft_check_ceiling(line_split, &mapfile->ceiling); //borrar
       	printf("%d %d %d\n",mapfile->ceiling.red,mapfile->ceiling.green, mapfile->ceiling.blue); //borrar
       	result = ft_check_floor(line_split, &mapfile->floor); //borrar
       	printf("%d %d %d\n",mapfile->floor.red,mapfile->floor.green, mapfile->floor.blue); //borrar
  //       i = 0;
  //       while (i < ft_count_words(line, ' '))
  //       {
		// 	ft_putstr(line_split[i]);
  //     		ft_putstr(",");
		// 	i++;
		// }
		// ft_putstr("\n");

	 	free(line);
	}
    return (0);
}


int ft_check_resolution(char **line, t_screen *resolution)
{
	if (line[0] && line[0][0] == 'R')
	{
		if (line[3])
			return (ft_put_error("more arguments than expected for res"));
		if (!line[1] || !line[2])
			return (ft_put_error("invalid arguments for resolution"));
		if (!ft_isnumber(line[1]) || !ft_isnumber(line[2]))
			return (ft_put_error("is not number for resolution"));
		resolution->width = ft_atoi(line[1]);
		resolution->height = ft_atoi(line[2]);

		printf ("ancho %d \n", resolution->width); // borrar
		printf ("altura %d \n", resolution->height); //borrar

		if (resolution->width <= 0 || resolution->height <= 0)
			return(ft_put_error("Resolution must be greater than 0"));
	}
	// printf ("%d\n", resolution.width);


	// //borrar prueba
	// while (line[i])
 //    {

	// 	printf ("%s\n", line[i]);
	// 	i++;
	// }
	// printf("\n");
	return (0);
}

int ft_check_ceiling(char **line, t_color *ceiling)
{
	// int i;
	// i = 0;
	// while(line[i])
	// {
	// 	printf("helo %d %s\n", i, line[i]);
	// 	i++;
	// }

	if (line[0] && line[0][0] == 'C')
	{
		if (line[4])
			return (ft_put_error("more arguments than expected"));
		if (!line[1] || !line[2] || !line[3])
			return (ft_put_error("invalid arguments"));
		if (!ft_check_valid_color(line[1]) || !ft_check_valid_color(line[2])
			|| !ft_isnumber(line[3])) 
			return (ft_put_error("Some arguments are not numbers"));
		ceiling->red = atoi(line[1]);
		ceiling->green = atoi(line[2]);
		ceiling->blue = atoi(line[3]);
		printf ("red ceiling %d \n", ceiling->red); // borrar
		printf ("blue ceiling %d \n", ceiling->green); //borrar
		printf ("green ceiling %d \n", ceiling->blue); //borrar

		if (ceiling->red < 0 || ceiling->green < 0 || ceiling->blue < 0)
			return(ft_put_error("Non negative numbers are expected"));
		if (ceiling->red > 255 || ceiling->green > 255 || ceiling->blue > 255)
			return(ft_put_error("Color value(s) must be maximum 255"));
	}
	
	// //borrar prueba
	// while (line[i])
 //    {

	// 	printf ("%s\n", line[i]);
	// 	i++;
	// }
	// printf("\n");
	return (0);
}

int ft_check_floor(char **line, t_color *floor)
{
	if (line[0] && line[0][0] == 'F')
	{
		if (line[4])
			return (ft_put_error("more arguments than expected"));
		if (!line[1] || !line[2] || !line[3])
			return (ft_put_error("invalid arguments"));
		if (!ft_check_valid_color(line[1]) || !ft_check_valid_color(line[2])
			|| !ft_isnumber(line[3])) 
			return (ft_put_error("Some of this arguments are not numbers"));
		floor->red = atoi(line[1]);
		floor->green = atoi(line[2]);
		floor->blue = atoi(line[3]);
		printf ("red floor %d \n", floor->red); // borrar
		printf ("blue floor %d \n", floor->green); //borrar
		printf ("green floor %d \n", floor->blue); //borrar

		if (floor->red < 0 || floor->green < 0 || floor->blue < 0)
			return(ft_put_error("Non negative numbers are expected"));
		if (floor->red > 255 || floor->green > 255 || floor->blue > 255)
			return(ft_put_error("Color value(s) must be maximum 255"));
	}
	//borrar prueba
	// while (line[i])
 	// {
	// 	printf ("%s\n", line[i]);
	// 	i++;
	// }
	// printf("\n");
	return (0);
}

// t_input ft_read_file_map(char *file_name)
// {
//     int 	ret;
//     int 	fd;
//     char 	*line;
//   	int 	i;
//   	char	**line_split;
//   	t_input resul;

//     ret = 1;
//     fd = open(file_name, O_RDONLY);
//     while (ret > 0)
//     {
//         ret = get_next_line(fd, &line);
//         if (ret < 0)
//         {
//       		ft_put_error("File not found");
//       		return (resul);
//         }
//         line_split = ft_split(line,' ');
//         i = 0;
//         while (i < ft_count_words(line, ' '))
//         {
// 			ft_putstr(line_split[i]);
//       		ft_putstr(",");
// 			i++;
// 		}
// 		ft_putstr("\n");
// 	 	free(line);
// 	}
//     return (resul);
// }

int main (int argc, char **argv)
{
	int screenshot;
	int error;
	t_input file_map;
	int result;

	error = 0;
	if (argc < 2)
		return(ft_put_error("at least one argument was expected"));
	if (argc > 3)
		return(ft_put_error("too many arguments"));
	if (argc >= 2)
	{
		if (ft_check_file_type(argv[1]) == -1)
		{
			ft_put_error("wrong extension map file");
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
		return(0);

	// file_map = ft_read_file_map(argv[1]);
	result = ft_read_file_map(argv[1], &file_map);

	if (result == -1)
		return (-1);
	// if (file_map == NULL)
	// 	return (-1);

	return (0);
}


//$ gcc parsing.c ft_split.c gnl/get_next_line.c cub3d_utils.c

