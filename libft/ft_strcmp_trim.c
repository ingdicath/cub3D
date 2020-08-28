/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcmp_trim.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/20 13:59:12 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/28 09:50:50 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strcmp_trim(const char *s1, const char *s2)
{
	char	*white_spaces;
	int		result;
	char	*temp;

	white_spaces = " \t\n\v\f\r";
	temp = ft_strtrim(s1, white_spaces);
	result = ft_strcmp(temp, s2);
	free(temp);
	return (result);
}
