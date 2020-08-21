#include "cub3d.h"
#include <stdio.h>

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

int		ft_check_resolution(char **line, t_win_size *win_size)
{
	if (line[0] && (ft_strcmp(line[0], "R") == 0))
	{
		if (win_size->width >= 0 || win_size->height >= 0)
			return (ft_put_error("argument(s) for RES already exist(s)"));
		if (ft_array_size(line) != 3)
			return (ft_put_error("wrong number of arguments for RES"));
		if (!ft_isnumber(line[1]) || !ft_isnumber(line[2]))
			return (ft_put_error("is not number for resolution"));
		win_size->width = ft_atoi(line[1]);
		win_size->height = ft_atoi(line[2]);
		if (win_size->width <= 0 || win_size->height <= 0)
			return (ft_put_error("Resolution must be greater than 0"));
	}
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
		if (floor->red < 0 || floor->green < 0 || floor->blue < 0)
			return (ft_put_error("Non negative numbers are expected"));
		if (floor->red > 255 || floor->green > 255 || floor->blue > 255)
			return (ft_put_error("Color value(s) must be maximum 255"));
	}
	return (1);
}
