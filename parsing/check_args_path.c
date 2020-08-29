/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_args_path.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:07:06 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/26 13:23:38 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			ft_parsing(int argc, char **argv, t_game_file *file, int *scrshot)
{
	int		res;

	ft_reset_input(file);
	res = ft_check_args(argc, argv, scrshot) &&
		ft_read_file(argv[1], file) &&
		ft_set_sprites_and_orientation(&file->map) &&
		ft_check_map(file->map);
	return (res);
}

int			ft_check_args(int argc, char **argv, int *screenshot)
{
	int		error;

	*screenshot = 0;
	error = 1;
	if (argc < 2)
		return (ft_put_error("at least one argument was expected"));
	if (argc > 3)
		return (ft_put_error("too many arguments"));
	if (argc >= 2)
	{
		if (!ft_check_extension(argv[1], CUB))
			error = ft_put_error("wrong extension in map file");
		if (argc == 3)
		{
			if (ft_strcmp(argv[2], "--save") == 0)
				*screenshot = 1;
			else
				error = ft_put_error("wrong argument for screenshot");
		}
	}
	return (error);
}

int			ft_check_extension(char *file_name, char *valid_ext)
{
	int		name_size;
	int		ext_size;
	char	*temp;
	int		res;

	res = 0;
	name_size = ft_strlen(file_name);
	ext_size = ft_strlen(valid_ext);
	temp = ft_substr(file_name, (name_size - ext_size), name_size);
	if (ft_strcmp(temp, valid_ext) == 0)
		res = 1;
	free(temp);
	return (res);
}

int			ft_check_path(char *str)
{
	int		ret;
	int		i;

	i = 0;
	if (str[i] != '.')
		return (ft_put_error("invalid path"));
	if (!ft_check_extension(str, XPM) && !ft_check_extension(str, PNG))
		return (ft_put_error("invalid extension for texture"));
	ret = open(str, O_RDONLY);
	if (ret < 0)
		return (ft_put_error("file does not exist."));
	close(ret);
	return (1);
}

int			ft_check_valid_char(char c)
{
	if (c != '0' && c != '1' && c != '2' && c != ' ' && c != 'N' && c != 'S' &&
			c != 'W' && c != 'E')
		return (0);
	return (1);
}
