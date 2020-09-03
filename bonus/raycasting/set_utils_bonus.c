/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 13:48:24 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/28 10:23:41 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int		ft_resize_resolution(t_screen *screen)
{
	mlx_get_screen_size(screen->mlx, &screen->max_res.width,
		&screen->max_res.height);
	if (screen->max_res.width <= 0 || screen->max_res.height <= 0)
		return (ft_put_error("mlx screen resolution failure"));
	if (screen->resolution.width > screen->max_res.width)
		screen->resolution.width = screen->max_res.width;
	if (screen->resolution.height > screen->max_res.height)
		screen->resolution.height = screen->max_res.height;
	return (1);
}

int		ft_set_texture(void *mlx, char *path, t_texture *texture)
{
	if (ft_check_extension(path, XPM))
		texture->image = mlx_xpm_file_to_image(mlx, path,
			&texture->width, &texture->height);
	else if (ft_check_extension(path, PNG))
	{
		texture->image = mlx_png_file_to_image(mlx, path,
			&texture->width, &texture->height);
	}
	free(path);
	if (texture->image == NULL)
		return (ft_put_error("invalid path for texture or xpm res is >2048"));
	texture->address = mlx_get_data_addr(texture->image,
		&texture->bits_per_pixel, &texture->size_line, &texture->endian);
	if (texture->address == NULL)
		return (ft_put_error("image for texture failure"));
	return (1);
}

void	ft_free_memory(t_map *map)
{
	ft_free_array(map->matrix);
	free(map->zbuffer);
	free(map->sprites);
}
