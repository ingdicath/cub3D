/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_args_path.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:07:06 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/25 12:42:10 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			ft_check_args(int argc, char **argv, int *screenshot)
{
	int		error;

	*screenshot = 0;
	error = 0;
	if (argc < 2)
		return (ft_put_error("at least one argument was expected"));
	if (argc > 3)
		return (ft_put_error("too many arguments"));
	if (argc >= 2)
	{
		if (!ft_check_extension(argv[1], CUB))
		{
			ft_put_error("wrong extension in map file");
			error++;
		}
		if (argc == 3)
		{
			if (ft_strcmp(argv[2], "--save") == 0)
				*screenshot = 1;
			else
			{
				ft_put_error("wrong argument for screenshot");
				error++;
			}
		}
	}
	if (error > 0)
		return (0);
	return (1);
}

int			ft_check_extension(char *file_name, char *valid_ext)
{
	int		name_size;
	int		ext_size;
	char	*temp;

	name_size = ft_strlen(file_name);
	ext_size = ft_strlen(valid_ext);
	temp = ft_substr(file_name, (name_size - ext_size), name_size);
	if (ft_strcmp(temp, valid_ext) == 0)
		return (1);
	return (0);
}

int			ft_check_path(char *str)
{
	int		ret;
	int		i;

	i = 0;
	if (str[i] != '.')
		return (ft_put_error("invalid path"));
	if (!ft_check_extension(str, XPM) && !ft_check_extension(str, PNG)) // si no se va a usar PNG BORRAR
		return (ft_put_error("invalid extension for texture"));
	ret = open(str, O_RDONLY);
	if (ret < 0)
		return (ft_put_error("file does not exist."));
	close(ret);
	return (1);
}
