/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/15 14:57:45 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/20 16:54:33 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_read_buffer(int fd, char **remainder)
{
	static char	buf[BUFFER_SIZE + 1];
	int			index_buf;

	index_buf = 1;
	while (index_buf)
	{
		index_buf = read(fd, buf, BUFFER_SIZE);
		if (index_buf < 0)
			return (-1);
		buf[index_buf] = '\0';
		*remainder = ft_strjoin(*remainder, buf);
		if (*remainder == NULL)
			return (-1);
		if (ft_strchr(*remainder, '\n'))
			break ;
	}
	return (index_buf > 0 ? 1 : 0);
}

static int		ft_break_index(char *remainder)
{
	int			i;

	i = 0;
	while (remainder[i] != '\n' && remainder[i] != '\0')
		i++;
	return (i);
}

static int		ft_extract_line(char **remainder, char **line)
{
	int			i;
	int			res;
	char		*temp;

	i = ft_break_index(*remainder);
	*line = ft_substr(*remainder, 0, i);
	temp = *remainder;
	*remainder = ft_substr(temp, i + 1, ft_strlen(temp));
	if (temp[i] == '\0')
		res = 0;
	else
		res = 1;
	free(temp);
	return (res);
}

int				get_next_line(int fd, char **line)
{
	static char *remainder;
	int			read_result;

	if (fd < 0 || read(fd, 0, 0) == -1 || line == NULL)
		return (-1);
	if (remainder == NULL)
		remainder = ft_strdup("");
	read_result = ft_read_buffer(fd, &remainder);
	if (read_result < 0)
	{
		free(remainder);
		remainder = NULL;
	}
	else
	{
		read_result = ft_extract_line(&remainder, line);
		if (read_result == 0)
		{
			free(remainder);
			remainder = NULL;
		}
	}
	return (read_result);
}
