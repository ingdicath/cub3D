/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/13 14:38:08 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/07/13 14:50:37 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <"cub3d.h">

void	ft_putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

int     ft_puterror(char *error)
{
    ft_putstr_fd("Error:\n", 1);
    ft_putstr_fd(error, 1);
    return(-1);
}