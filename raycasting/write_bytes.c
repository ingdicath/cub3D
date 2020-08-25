/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_bytes.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:55:09 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/25 09:55:21 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_write_int_bytes(int fd, int param)
{
	write(fd, &param, FOUR_BYTES);
}

void	ft_write_short_bytes(int fd, int param)
{
	write(fd, &param, TWO_BYTES);
}

void	ft_write_char_zeros(int fd, int times)
{
	int i;

	i = 0;
	while (i < times)
	{
		write(fd, "\0", ONE_BYTE);
		i++;
	}
}
