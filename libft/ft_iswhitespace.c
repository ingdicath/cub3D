/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_iswhitespace.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/20 13:59:12 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/20 14:56:54 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_iswhitespace(char c)
{
	return (c == '\t' || c == '\n' || c == ' ' || c == '\v' || c == '\f'
		|| c == '\r');
}




int	ft_strcmp_trim(char *s1, const char *s2)
{
	char  *white_spaces;
	//char  *s1_trimmed;
	white_spaces = " \t\n\v\f\r";

	s1 = ft_strtrim(s1,white_spaces);

	return ft_strcmp(s1,s2);	
}