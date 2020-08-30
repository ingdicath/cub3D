/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_textures_path.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:46:37 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/28 09:55:39 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int		ft_check_north_path(char **line, char **north_path)
{
	if (line[0] && (ft_strcmp_trim(line[0], "NO") == 0))
	{
		if (*north_path != NULL)
			return (ft_put_error("argument(s) already for NO exist(s)"));
		if (!line[1])
			return (ft_put_error("invalid arguments for NO texture"));
		if (line[2])
			return (ft_put_error("more arguments than expected for NO text."));
		if (ft_check_path(line[1]))
			*north_path = ft_strdup(line[1]);
	}
	return (1);
}

int		ft_check_south_path(char **line, char **south_path)
{
	if (line[0] && (ft_strcmp_trim(line[0], "SO") == 0))
	{
		if (*south_path != NULL)
			return (ft_put_error("argument(s) already for SO exist(s)"));
		if (!line[1])
			return (ft_put_error("invalid arguments for SO texture"));
		if (line[2])
			return (ft_put_error("more arguments than expected for SO text."));
		if (ft_check_path(line[1]))
			*south_path = ft_strdup(line[1]);
	}
	return (1);
}

int		ft_check_west_path(char **line, char **west_path)
{
	if (line[0] && (ft_strcmp_trim(line[0], "WE") == 0))
	{
		if (*west_path != NULL)
			return (ft_put_error("argument(s) already for WE exist(s)"));
		if (!line[1])
			return (ft_put_error("invalid arguments WE texture"));
		if (line[2])
			return (ft_put_error("more arguments than expected for WE text."));
		if (ft_check_path(line[1]))
			*west_path = ft_strdup(line[1]);
	}
	return (1);
}

int		ft_check_east_path(char **line, char **east_path)
{
	if (line[0] && (ft_strcmp_trim(line[0], "EA") == 0))
	{
		if (*east_path != NULL)
			return (ft_put_error("argument(s) already for EA exist(s)"));
		if (!line[1])
			return (ft_put_error("invalid arguments for EA texture"));
		if (line[2])
			return (ft_put_error("more arguments than expected for EA text."));
		if (ft_check_path(line[1]))
			*east_path = ft_strdup(line[1]);
	}
	return (1);
}

int		ft_check_sprite_path(char **line, char **sprite_path)
{
	if (line[0] && (ft_strcmp_trim(line[0], "S") == 0))
	{
		if (*sprite_path != NULL)
			return (ft_put_error("argument(s) already for sprite exist(s)"));
		if (!line[1])
			return (ft_put_error("invalid arguments for sprite texture"));
		if (line[2])
			return (ft_put_error("more arguments than expected for texture"));
		if (ft_check_path(line[1]))
			*sprite_path = ft_strdup(line[1]);
	}
	return (1);
}
