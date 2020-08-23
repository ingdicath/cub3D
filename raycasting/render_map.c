#include "../cub3d.h"

/*
** map.matrix[y][x] in this order of x and y, North face up
**
*/

void	ft_perform_dda(t_map map, t_ray *ray)
{
	int	hit;
	int x;
	int y;

	hit = 0;
	while (hit == 0)
	{
		// //printf("Hit %d\n", hit);
		// //printf("antes valor de ray->sidedist.x  %f\n", ray->sidedist.x);
		// //printf("antes valor de ray->sidedist.y  %f\n", ray->sidedist.y);
		if (ray->sidedist.x < ray->sidedist.y)
		{
			ray->sidedist.x += ray->deltadist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			// //printf("No son iguales \n");
			ray->sidedist.y += ray->deltadist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		x = (int)ray->map.x;
		y = (int)ray->map.y;
		//printf("checking map  %d %d %c\n", x , y , map.matrix[x][y]);//borrar

		if (map.matrix[y][x] == '1') {
		/// revisar esta linea //(game->map.matrix[ray->map_x][ray->map_y] == '1') /// esto es el muro. porque es 1
		// //printf("jugo\n");
			hit = 1;
		}
	}
}
// Now, before the actual DDA can start, first stepX, stepY,
// and the initial 

void			ft_calc_side_dist(t_position current, t_ray *ray)
{
	// //printf("ray->dir.x %f\n", ray->dir.x );
	// //printf("ray->dir.y %f\n", ray->dir.y );
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->sidedist.x = (current.x - ray->map.x) * ray->deltadist.x;
		//printf("Operation mapX %f, startX  %f , deltadist %f\n", ray->map.x,current.x,ray->deltadist.x);
		//printf("uno ray->sidedist.x  %f\n", ray->sidedist.x);
	}
	else
	{
		ray->step.x = 1;
		ray->sidedist.x = (ray->map.x + 1.0 - current.x) * ray->deltadist.x;
		//printf("Operation mapX %f, startX  %f , deltadist %f\n", ray->map.x,current.x,ray->deltadist.x);
		//printf("dos ray->sidedist.x  %f\n", ray->sidedist.x);
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->sidedist.y = (current.y - ray->map.y) * ray->deltadist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sidedist.y = (ray->map.y + 1.0 - current.y) * ray->deltadist.y;
	}
	// //printf("before dda ray->sidedist.x  %lf\n", ray->sidedist.x);
	// //printf("before dda ray->sidedist.y  %f\n", ray->sidedist.y);
}

void	ft_set_ray_position(t_game *game, int x)  /// check this
{
	t_ray		*ray;

	ray = &game->player.ray;
	// //printf("loading player  %f %f\n", game->player.direction.x  ,game->player.direction.y);
	ray->camera_x = 2 * x / (double)game->screen.resolution.width - 1;
	
	ray->dir.x = game->player.orientation.x +
			game->player.plane.x * ray->camera_x;
	ray->dir.y = game->player.orientation.y +
			game->player.plane.y * ray->camera_x;
	
	ray->map.x = (int)game->player.current_pos.x; // map x revisar valor entero
	ray->map.y = (int)game->player.current_pos.y;

	//printf("Ray dir pos  %f %f\n", ray->dir.x  , ray->dir.y); //borrar
	// printf("Ray map pos  %f %f\n", ray->map.x  , ray->map.y); //borrar

	ray->deltadist.x = fabs(1 / ray->dir.x);
	ray->deltadist.y = fabs(1 / ray->dir.y);
	////printf("loading delta  %f %f\n", ray->deltadist.x  , ray->deltadist.y);
}

void			ft_render_map(t_game *game)
{
	int			x;

	//printf("resoultion W%d, H%d\n", game->screen.resolution.width, game->screen.resolution.height); //borrar
	x = 0;
	while (x < game->screen.resolution.width)
	{
		ft_set_ray_position(game, x);
		ft_calc_side_dist(game->player.current_pos, &game->player.ray);
		ft_perform_dda(game->map, &game->player.ray);
		ft_calc_wall_dist(&game->player.ray, game->player.current_pos);
		ft_calc_draw_limits(&game->player.ray, game->screen.resolution);
		ft_calc_wall_pos(&game->player.ray, &game->screen.wall, game->player.current_pos); // REVISAR SI CAMBIA CONSTANTE POR TEXTURA
		ft_draw_walls(&game->player.ray, &game->screen, x);
		game->map.zbuffer[x] = game->player.ray.perpwalldist;
		
		ft_draw_floor_ceiling(&game->screen, game->player.ray, x);
		ft_render_sprites(game);
		x++;
	}


	mlx_put_image_to_window(game->screen.mlx, game->screen.window,
		game->screen.win_data.image, 0, 0);
	//printf("Poniendo imagen %p %d\n",game->screen.win_data.address, game->screen.win_data.size_line ); //borrar
}