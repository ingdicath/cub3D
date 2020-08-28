/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/20 13:38:52 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/20 16:47:51 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*string;
	size_t	i;
	size_t	length;

	if (!s)
		return (NULL);
	length = ft_strlen(s);
	if (start > length)
		return (ft_strdup(""));
	if (length - start < len)
		len = length - start;
	string = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	while (s[start] != '\0' && i < len)
	{
		string[i] = s[start];
		start++;
		i++;
	}
	string[i] = '\0';
	return (string);
}
