/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/20 13:37:39 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/20 16:47:06 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}
