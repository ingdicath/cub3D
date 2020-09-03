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

int		ft_check_tex_floor(char *header, char *element, char **floor_path)
{
	if (ft_strcmp(header, "F") == 0)
	{
		if (*floor_path != NULL)
			return (ft_put_error("argument(s) already for F exist(s)"));
		else if (!element)
			return (ft_put_error("invalid arguments for F texture"));
		else if (ft_check_path(element))
			*floor_path = ft_strdup(element);
		else
			return (0);
	}
	return (1);
}

int		ft_check_tex_ceiling(char *header, char *element, char **ceil_path)
{
	if (ft_strcmp(header, "C") == 0)
	{
		if (*ceil_path != NULL)
			return (ft_put_error("argument(s) already for C exist(s)"));
		else if (!element)
			return (ft_put_error("invalid arguments for C texture"));
		else if (ft_check_path(element))
			*ceil_path = ft_strdup(element);
		else
			return (0);
	}
	return (1);
}
