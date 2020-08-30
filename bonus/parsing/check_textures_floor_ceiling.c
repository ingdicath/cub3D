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

int		ft_check_tex_floor(char **line, char **floor_path)
{
	if (line[0] && (ft_strcmp_trim(line[0], "F") == 0))
	{
		if (*floor_path != NULL)
			return (ft_put_error("argument(s) already for F exist(s)"));
		if (!line[1])
			return (ft_put_error("invalid arguments for F texture"));
		if (line[2])
			return (ft_put_error("more arguments than expected for F text."));
		if (ft_check_path(line[1]))
			*floor_path = ft_strdup(line[1]);
	}	
	return (1);
}

int		ft_check_tex_ceiling(char **line, char **ceil_path)
{
	if (line[0] && (ft_strcmp_trim(line[0], "C") == 0))
	{
		if (*ceil_path != NULL)
			return (ft_put_error("argument(s) already for C exist(s)"));
		if (!line[1])
			return (ft_put_error("invalid arguments for C texture"));
		if (line[2])
			return (ft_put_error("more arguments than expected for C text."));
		if (ft_check_path(line[1]))
			*ceil_path = ft_strdup(line[1]);
	}
	return (1);
}
