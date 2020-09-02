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

int		ft_check_north_path(char *header, char *element, char **north_path)
{
	if (ft_strcmp(header, "NO") == 0)
	{
		if (*north_path != NULL)
			return (ft_put_error("argument(s) already for NO exist(s)"));
		if (!element)
			return (ft_put_error("invalid arguments for NO texture"));
		if (ft_check_path(element))
			*north_path = ft_strdup(element);
	}
	return (1);
}

int		ft_check_south_path(char *header, char *element, char **south_path)
{
	if (ft_strcmp(header, "SO") == 0)
	{
		if (*south_path != NULL)
			return (ft_put_error("argument(s) already for SO exist(s)"));
		if (!element)
			return (ft_put_error("invalid arguments for SO texture"));
		if (ft_check_path(element))
			*south_path = ft_strdup(element);
	}
	return (1);
}

int		ft_check_west_path(char *header, char *element, char **west_path)
{
	if (ft_strcmp(header, "WE") == 0)
	{
		if (*west_path != NULL)
			return (ft_put_error("argument(s) already for WE exist(s)"));
		if (!element)
			return (ft_put_error("invalid arguments for WE texture"));
		if (ft_check_path(element))
			*west_path = ft_strdup(element);
	}
	return (1);
}

int		ft_check_east_path(char *header, char *element, char **east_path)
{
	if (ft_strcmp(header, "EA") == 0)
	{
		if (*east_path != NULL)
			return (ft_put_error("argument(s) already for EA exist(s)"));
		if (!element)
			return (ft_put_error("invalid arguments for EA texture"));
		if (ft_check_path(element))
			*east_path = ft_strdup(element);
	}
	return (1);
}

int		ft_check_sprite_path(char *header, char *element, char **sprite_path)
{
	if (ft_strcmp(header, "S") == 0)
	{
		if (*sprite_path != NULL)
			return (ft_put_error("argument(s) already for sprite exist(s)"));
		if (!element)
			return (ft_put_error("invalid arguments for sprite texture"));
		if (ft_check_path(element))
			*sprite_path = ft_strdup(element);
	}
	return (1);
}
