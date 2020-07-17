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

int ft_check_file_type(char *map_ext)
{
    int i;
    
    i = ft_strlen(map_ext);
    if (map_ext[i - 4] == '.' && map_ext[i - 3] == 'c' && map_ext[i - 2] == 'u'
        && map_ext[i - 1] == 'b')
            return (1);
    return(-1);
}

// Pendiente por completar
int *ft_open_map_file   (char *map_name)
{
    int fd;
    char *line;

    fd = open(map_name, O_RDONLY);
    if (ft_check_file_type(map_name) == -1 || fd < 0)
        return(ft_put_error("Can not open .cub map file"));
    line = 
}

int main (int argc, char **argv)
{
	int screenshot;
	int error;

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
	return (0);
}

t_screen ft_check_resolution(char *line)
{
	int i;
	
	i = 0;
	while (line[i] != '\0')
	{
		if (ft_iswhitespace(line[i]))
		{
			i++;
			continue ;
		}
		if (line[i] == 'R')
			i++;

	}








	if ()
	if (!input.width || !input.height)
		return(ft_put_error("it must be two arguments"));
	if (input.width < 0 || res.height < 0)
		return(ft_put_error("Non negative numbers were expected"));
	if (res.width > max_color_val || res.height > max_color_val )
		return(ft_put_error("Color value(s) must be maximun 255"));
	if (!res.width || !res.width)

}


