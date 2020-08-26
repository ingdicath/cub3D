/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_res_floor_ceiling_color.c                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:48:02 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/25 13:08:38 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

int			ft_array_size(char **array)
{
	int		i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

/*
** width or height bigger than 16384 for screenshot rendering
*/

int			ft_check_resolution(char **line, t_size *resolution)
{
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
		if (resolution->width <= 0 || resolution->height <= 0)
			return (ft_put_error("Invalid value for Resolution"));
		if (resolution->width > 16384 || resolution->height > 16384)
			return (ft_put_error("Resolution exceeds maximum value 16384"));
	}
	return (1);
}

int			ft_check_ceiling(char **line, t_color *ceiling)
{
	if (line[0] && (ft_strcmp(line[0], "C") == 0))
	{
		if (ceiling->red >= 0 || ceiling->green >= 0 || ceiling->blue >= 0)
			return (ft_put_error("argument(s) already for ceiling exist(s)"));
		if (!line[1] || !line[2] || !line[3])
			return (ft_put_error("missing arguments for ceiling"));
		if (line[4])
			return (ft_put_error("more arguments for ceiling than expected."));	
		if (!ft_check_valid_color(line[1]) || !ft_check_valid_color(line[2])
			|| !ft_isnumber(line[3]))
			return (ft_put_error("ceiling: check numbers or missing commas"));
		ceiling->red = atoi(line[1]);
		ceiling->green = atoi(line[2]);
		ceiling->blue = atoi(line[3]);
		if (ceiling->red < 0 || ceiling->green < 0 || ceiling->blue < 0)
			return (ft_put_error("ceil.: Non negative numbers are expected"));
		if (ceiling->red > 255 || ceiling->green > 255 || ceiling->blue > 255)
			return (ft_put_error("ceiling: color value must be maximum 255"));
	}
	return (1);
}

int			ft_check_floor(char **line, t_color *floor)
{
	if (line[0] && (ft_strcmp(line[0], "F") == 0))
	{
		if (floor->red >= 0 || floor->green >= 0 || floor->blue >= 0)
			return (ft_put_error("argument(s) already for floor exist(s)"));
		if (!line[1] || !line[2] || !line[3])
			return (ft_put_error("missing arguments for floor"));
		if (line[4])
			return (ft_put_error("more arguments for floor than expected"));
		if (!ft_check_valid_color(line[1]) || !ft_check_valid_color(line[2])
			|| !ft_isnumber(line[3]))
			return (ft_put_error("floor: check numbers or missing commas"));
		floor->red = atoi(line[1]);
		floor->green = atoi(line[2]);
		floor->blue = atoi(line[3]);
		if (floor->red < 0 || floor->green < 0 || floor->blue < 0)
			return (ft_put_error("floor: Non negative numbers are expected"));
		if (floor->red > 255 || floor->green > 255 || floor->blue > 255)
			return (ft_put_error("floor: color value must be maximum 255"));
	}
	return (1);
}
