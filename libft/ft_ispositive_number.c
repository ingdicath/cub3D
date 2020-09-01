/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ispositive_number.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/01 13:50:26 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/09/01 13:51:54 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_ispositive_number(char *str)
{
	int		i;
	char	*no_space;
	char	*white_spaces;

	white_spaces = " \t\n\v\f\r";
	no_space = ft_strtrim(str, white_spaces);
	i = 0;
	if (no_space[i] == '\0')
	{
		free(no_space);
		return (0);
	}
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
