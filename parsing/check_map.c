/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 08:27:09 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/25 12:48:24 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//borrar
void	print_map(char **map)
{
	int i = 0;
	while (map[i] != NULL)
	{
		// printf("mapa:) %s\n",map[i]);
		i++;
	}
}

int		ft_check_map(t_map map)
{
	int	res;

	//print_map(map.matrix); //borrar
	res = ft_flood_fill(map.matrix, map.start_pos.x, map.start_pos.y)
	//print_map(map.matrix); //borrar
	&& ft_uncovered_map(map.matrix);
	// print_map(map.matrix); //borrar
	if (!res)
		return (ft_put_error("Invalid map"));
	return (res);
}

int		ft_flood_fill(char **matrix, int x, int y)
{
	int	res;

	// printf("pos x %d, pos y %d\n", x, y);
	res = 1;
	if (!res && matrix[y][x] != '+' && !ft_check_valid_char(matrix[y][x]))
		return (0);
	if (matrix[y][x] == '1' || matrix[y][x] == '*' || matrix[y][x] == '+')
		return (res);
	else if (matrix[y][x] == '0' || matrix[y][x] == '2')
	{
		if (matrix[y][x] == '0')
			matrix[y][x] = '+';
		else
			matrix[y][x] = '*';
		res = res && ft_flood_fill(matrix, x - 1, y);
		res = res && ft_flood_fill(matrix, x, y - 1);
		res = res && ft_flood_fill(matrix, x + 1, y);
		res = res && ft_flood_fill(matrix, x, y + 1);
		res = res && ft_flood_fill(matrix, x - 1, y - 1);
		res = res && ft_flood_fill(matrix, x - 1, y + 1);
		res = res && ft_flood_fill(matrix, x + 1, y + 1);
		res = res && ft_flood_fill(matrix, x + 1, y - 1);
	}
	else
		return (0);
	return (res);
}

int		ft_uncovered_map(char **matrix)
{
	int	i;
	int	j;

	i = 0;
	while (matrix[i] != NULL)
	{
		j = 0;
		while (matrix[i][j] != '\0')
		{
			if (matrix[i][j] == '0')
			{
				// print_map(matrix); //borrar
				if (!ft_flood_fill(matrix, j, i))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
