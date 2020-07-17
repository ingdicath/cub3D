/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 11:02:40 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/07/16 20:51:48 by dsalaman      ########   odam.nl         */
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


// falta reemplazar en la funcion open, que abra cualquier archivo de tipo cub




int ft_read_map(int fd, char **res)
{
    int 	ret;
    char 	*line;
  	int 	i;

    ret = 1;
    fd = open("valid_map.cub", O_RDONLY);
    while (ret > 0)
    {
        ret = get_next_line(fd, &line);
        res = ft_split(line,' ');
        i = 0;
        while (i < ft_count_words(line, ' '))
        {
			ft_putstr(res[i]);
      		ft_putstr(",");
			i++;
		}
		ft_putstr("\n");
	 	free(line);
	}
    return (1);
}

// Pendiente por completar
// int *ft_open_map_file   (char *map_name)
// {
//     int fd;
//     char *line;

//     fd = open(map_name, O_RDONLY);
//     if (ft_check_file_type(map_name) == -1 || fd < 0)
//         return(ft_put_error("Can not open .cub map file"));
//     line = 
// }

int main (int argc, char **argv)
{
	int screenshot;
	int error;
	char *line;

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

	ft_read_map(argv[1], &line);
	return (0);
}

// t_screen ft_check_resolution(char *line)
// {
// 	int i;
	
// 	i = 0;
// 	while (line[i] != '\0')
// 	{
// 		if (ft_iswhitespace(line[i]))
// 		{
// 			i++;
// 			continue ;
// 		}
// 		if (line[i] == 'R')
// 			i++;

// 	}


// 	if ()
// 	if (!input.width || !input.height)
// 		return(ft_put_error("it must be two arguments"));
// 	if (input.width < 0 || res.height < 0)
// 		return(ft_put_error("Non negative numbers were expected"));
// 	if (res.width > max_color_val || res.height > max_color_val )
// 		return(ft_put_error("Color value(s) must be maximun 255"));
// 	if (!res.width || !res.width)

// }


