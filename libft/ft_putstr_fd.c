/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/20 13:35:52 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/20 13:45:29 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
