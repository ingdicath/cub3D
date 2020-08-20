/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_put_error.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/20 13:37:09 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/20 14:57:53 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_put_error(char *error)
{
	ft_putstr_fd("\nError:\n", 1);
	ft_putstr_fd(error, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}
