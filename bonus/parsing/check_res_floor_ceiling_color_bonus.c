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

#include "../cub3d_bonus.h"

/*
** The maximum max resolution mlx can handle is 16384.
*/

int			ft_check_resolution(char **line, t_size *resolution, int scrshot)
{
	if (line[0] && (ft_strcmp_trim(line[0], "R") == 0))
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
		if (scrshot == 1 && (resolution->width > 16384 ||
				resolution->height > 16384))
			return (ft_put_error("Resolution exceeds maximum value 16384"));
	}
	return (1);
}
