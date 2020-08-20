/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/20 13:38:05 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/20 16:46:10 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s1)
{
	char	*str;
	size_t	size;

	size = 0;
	while (s1[size] != '\0')
		size++;
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	size = 0;
	while (s1[size] != '\0')
	{
		str[size] = s1[size];
		size++;
	}
	str[size] = '\0';
	return (str);
}
