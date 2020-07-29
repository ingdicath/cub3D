/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 13:30:07 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/07/24 16:24:54 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_substr(char *s, unsigned int start, size_t len)
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

char		*ft_strchr(const char *s, int c)
{
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

char		*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s3;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	s3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (NULL);
	while (s1[i] != '\0')
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = '\0';
	free(s1);
	return (s3);
}
