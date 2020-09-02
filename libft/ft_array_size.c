/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_array_size.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/20 13:37:39 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/20 16:47:06 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_array_size(char **array)
{
	int		i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}
