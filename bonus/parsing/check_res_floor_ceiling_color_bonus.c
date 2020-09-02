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
