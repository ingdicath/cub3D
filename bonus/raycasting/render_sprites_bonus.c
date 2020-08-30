/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_sprites.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 08:29:41 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/28 10:27:46 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int					ft_render_sprites(t_game *game)
{
	int				i;
	t_sprite_cast	s_cast;

	i = 0;
	ft_sort_sprites(&game->map, game->player.current_pos);
	while (i < game->map.num_sprites)
	{
		ft_inverse_camera(game->map.sprites[i], &s_cast, game->player,
			game->screen.resolution.width);
		ft_calc_sprite_limits(&s_cast, game->screen.resolution,
			game->player.ray);
		ft_vertical_stripes(&s_cast, game->screen, game->map.zbuffer);
		i++;
	}
	return (0);
}

/*
** 'inv_camera'  = required for correct matrix multiplication.
** 'sprite_relative' = translate sprite position to relative to camera.
** 'transform y' = /this is the depth inside the screen.
*/

void				ft_inverse_camera(t_sprite sprite, t_sprite_cast *s_cast,
						t_player player, int w)
{
	double			inv_camera;
	t_position		sprite_relative;

	sprite_relative.x = sprite.position.x - player.current_pos.x;
	sprite_relative.y = sprite.position.y - player.current_pos.y;
	inv_camera = 1.0 / (player.plane.x * player.orientation.y -
		player.orientation.x * player.plane.y);
	s_cast->transform.x = inv_camera * (player.orientation.y *
		sprite_relative.x - player.orientation.x * sprite_relative.y);
	s_cast->transform.y = inv_camera * (-player.plane.y * sprite_relative.x +
		player.plane.x * sprite_relative.y);
	s_cast->screen_x = (int)((w / 2) *
		(1 + s_cast->transform.x / s_cast->transform.y));
}

/*
** Calculate height of the sprite on screen using 'transform y' instead of
** the real distance prevents fisheye.
*/

void				ft_calc_sprite_limits(t_sprite_cast *s_cast,
						t_size resolution, t_ray ray)
{
	s_cast->move_screen = (int)(V_MOVE / s_cast->transform.y) + ray.pitch +
							ray.pos_z / s_cast->transform.y;
	s_cast->size.height = abs((int)(resolution.height / s_cast->transform.y));
	s_cast->draw_start.y = (int)(-s_cast->size.height / 2 +
		resolution.height / 2) + s_cast->move_screen;
	if (s_cast->draw_start.y < 0)
		s_cast->draw_start.y = 0;
	s_cast->draw_end.y = (int)(s_cast->size.height / 2 +
		resolution.height / 2) + s_cast->move_screen;
	if (s_cast->draw_end.y >= resolution.height)
		s_cast->draw_end.y = resolution.height - 1.0;
	s_cast->size.width = abs((int)(resolution.height / s_cast->transform.y));
	s_cast->draw_start.x = (int)(-s_cast->size.width / 2 + s_cast->screen_x);
	if (s_cast->draw_start.x < 0)
		s_cast->draw_start.x = 0;
	s_cast->draw_end.x = (int)(s_cast->size.width / 2 + s_cast->screen_x);
	if (s_cast->draw_end.x >= resolution.width)
		s_cast->draw_end.x = resolution.width - 1.0;
}

/*
** ZBuffer is 1D, because it only contains the distance to the wall of
** every vertical stripe, instead of having this for every pixel.
*/

void				ft_vertical_stripes(t_sprite_cast *s_cast, t_screen screen,
						double *zbuffer)
{
	int				stripe;
	t_position		tex;

	stripe = s_cast->draw_start.x;
	while (stripe < s_cast->draw_end.x)
	{
		tex.x = (int)(256 * (stripe - (-s_cast->size.width / 2 +
			s_cast->screen_x)) *
		screen.sprite.width / s_cast->size.width) / 256;
		if (s_cast->transform.y > 0 && stripe > 0 &&
			stripe < screen.resolution.width &&
			s_cast->transform.y < zbuffer[stripe])
			ft_draw_stripes(s_cast, screen, &tex, stripe);
		stripe++;
	}
}

void				ft_draw_stripes(t_sprite_cast *s_cast, t_screen screen,
						t_position *tex, int stripe)
{
	int				color;
	int				y;
	int				d;

	y = s_cast->draw_start.y;
	while (y < s_cast->draw_end.y)
	{
		d = (y - s_cast->move_screen) * 256 - screen.resolution.height * 128 +
			s_cast->size.height * 128;
		tex->y = ((d * screen.sprite.height) / s_cast->size.height) / 256;
		color = ft_get_color(screen.sprite, *tex);
		if ((color & 0x00FFFFFF) != 0)
			ft_put_pixel(&screen.win_data, stripe, y, color);
		y++;
	}
}
