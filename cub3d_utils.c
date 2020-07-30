/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 12:55:18 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/07/29 12:55:49 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	ft_putstr_fd(char *str, int fd)
{
	int i;

	i = 0;
	if (!str)
		return ;
	while (str[i] != '\0')
	{
		write(fd, &str[i], 1);
		i++;
	}
}

int		ft_put_error(char *error)
{
	ft_putstr_fd("\nError:\n", 1);
	ft_putstr_fd(error, 1);
	ft_putstr_fd("\n", 1);
	return (-1);
}

/*
** ----- first file -----
*/

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

/*
** -----  second file -----
*/

int					ft_iswhitespace(char c)
{
	return (c == '\t' || c == '\n' || c == ' ' || c == '\v' || c == '\f'
		|| c == '\r');
}

int					ft_istab(char c)
{
	return (c == '\t' || c == '\v' || c == '\f' || c == '\r');
}

int					ft_isemptyline(char *str)
{
	int 			i;

	i = 0;
	if (str[i] == '\0')
		return (1);
	while (str[i] != '\0')
	{
		if (!ft_iswhitespace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int					ft_atoi(const char *str)
{
	unsigned long	result;
	int				i;
	int				sign;

	i = 0;
	result = 0;
	sign = 1;
	while (ft_iswhitespace(str[i]))
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
		if (result > 9223372036854775807 && sign == -1)
			return (0);
		else if (result > 9223372036854775807 && sign == 1)
			return (-1);
	}
	return (sign * result);
}

int					ft_isnumber(char *str)
{
	int 			i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int					ft_strcmp(const char *s1, const char *s2)
{
	size_t 			i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
