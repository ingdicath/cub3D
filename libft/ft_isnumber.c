/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isnumber.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/20 14:00:23 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/20 14:00:36 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int					ft_isnumber(char *str)
{
	int				i;

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