/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_res_floor_ceiling_color.c                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:48:02 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/28 10:17:25 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			ft_check_resolution(char *header, char *element, t_size *resolution)
{
	int		res;
	char	**line_split;

	res = 1;
	if (ft_strcmp(header, "R") == 0)
	{
		line_split = ft_split(element, ' ');
		if (resolution->width >= 0 || resolution->height >= 0)
			res = ft_put_error("argument(s) for RES already exist(s)");
		else if (ft_array_size(line_split) != 2)
			res = ft_put_error("wrong number of arguments for RES");
		else if (!ft_isnumber(line_split[0]) || !ft_isnumber(line_split[1]))
			res = ft_put_error("is not number for resolution");
		else
		{
			resolution->width = ft_atoi_max_int(line_split[0]);
			resolution->height = ft_atoi_max_int(line_split[1]);
			if (resolution->width <= 0 || resolution->height <= 0)
				res = ft_put_error("Invalid value for Resolution");
		}
		ft_free_array(line_split);
	}
	return (res);
}

int			ft_check_ceiling(char *header, char *element, t_color *ceiling)
{
	char	**colors;
	int		res;

	res = 1;
	if (ft_strcmp(header, "C") == 0)
	{
		colors = ft_split(element, ',');
		if (ceiling->red >= 0 || ceiling->green >= 0 || ceiling->blue >= 0)
			res = ft_put_error("argument(s) already for ceiling exist(s)");
		else if (ft_array_size(colors) != 3 || element[0] == ','
				|| element[(ft_strlen(element) - 1)] == ',')
			res = ft_put_error("Wrong number of arguments for ceiling.");
		else if (!ft_isnumber(colors[0]) || !ft_isnumber(colors[1])
				|| !ft_isnumber(colors[2]))
			res = ft_put_error("check numbers for ceiling");
		else
		{
			ceiling->red = atoi(colors[0]);
			ceiling->green = atoi(colors[1]);
			ceiling->blue = atoi(colors[2]);
			res = ft_check_rgb_color(*ceiling);
		}
		ft_free_array(colors);
	}
	return (res);
}

int			ft_check_rgb_color(t_color color)
{
	if (color.red < 0 || color.green < 0 || color.blue < 0)
		return (ft_put_error("Color: Value should not be negative"));
	else if (color.red > 255 || color.green > 255 || color.blue > 255)
		return (ft_put_error("Color: Value must be maximum 255"));
	else
		return (1);
}

int			ft_check_floor(char *header, char *element, t_color *floor)
{
	char	**colors;
	int		res;

	res = 1;
	if (ft_strcmp(header, "F") == 0)
	{
		colors = ft_split(element, ',');
		if (floor->red >= 0 || floor->green >= 0 || floor->blue >= 0)
			res = ft_put_error("argument(s) already for floor exist(s)");
		else if (ft_array_size(colors) != 3 || element[0] == ','
				|| element[(ft_strlen(element) - 1)] == ',')
			res = ft_put_error("Wrong number of arguments for floor.");
		else if (!ft_isnumber(colors[0]) || !ft_isnumber(colors[1])
				|| !ft_isnumber(colors[2]))
			res = ft_put_error("check numbers for floor");
		else
		{
			floor->red = atoi(colors[0]);
			floor->green = atoi(colors[1]);
			floor->blue = atoi(colors[2]);
			res = ft_check_rgb_color(*floor);
		}
		ft_free_array(colors);
	}
	return (res);
}
