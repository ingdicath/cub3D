/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isnumber.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/20 14:00:23 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/28 09:47:13 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_isnumber(char *str)
{
	int		i;
	char	*no_space;
	char	*white_spaces;

	white_spaces = " \t\n\v\f\r";
	no_space = ft_strtrim(str, white_spaces);
	i = 0;
	if (!no_space || no_space[i] == '\0')
	{
		free(no_space);
		return (0);
	}
	if (no_space[i] == '-')
		i++;
	while (no_space[i] != '\0')
	{
		if (no_space[i] < '0' || no_space[i] > '9')
		{
			free(no_space);
			return (0);
		}
		i++;
	}
	free(no_space);
	return (1);
}
