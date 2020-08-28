/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isnumber.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/20 14:00:23 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/20 14:57:20 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isnumber(char *str)
{
	int i;
	char  *no_space;
	char  *white_spaces;

	white_spaces = " \t\n\v\f\r";
	no_space = ft_strtrim(str,white_spaces);

	i = 0;
	if (no_space[i] == '-')
		i++;
	while (no_space[i] != '\0')
	{
		if (no_space[i] < '0' || no_space[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

char		*ft_strtrim(char  *s1, char  *set)
{
	size_t	i;
	size_t	j;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	i = 0;
	j = ft_strlen(s1) - 1;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	if (!s1[i])
		return (ft_strdup(""));
	while (s1[j] && ft_strchr(set, s1[j]))
		j--;
	return (ft_substr(s1, i, j - i + 1));
}