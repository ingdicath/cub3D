/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isemptyline.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/20 13:59:48 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/20 14:00:02 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int					ft_isemptyline(char *str)
{
	int				i;

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