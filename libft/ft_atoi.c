/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/20 13:57:07 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/20 13:57:15 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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