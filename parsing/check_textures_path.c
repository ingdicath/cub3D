#include "../cub3d.h"

int		ft_check_north_path(char **line, char **north_path)
{
	if (line[0] && (ft_strcmp(line[0], "NO") == 0))
	{
		if (*north_path != NULL)
			return (ft_put_error("argument(s) already for NO exist(s)"));
		if (line[2])
			return (ft_put_error("more arguments than expected for NO text."));
		if (!line[1])
			return (ft_put_error("invalid arguments for NO texture"));
		if (ft_check_path(line[1]))
			*north_path = line[1];
		printf("north texture %s\n", *north_path); // borrar
	}
	return (1);
}

int		ft_check_south_path(char **line, char **south_path)
{
	if (line[0] && (ft_strcmp(line[0], "SO") == 0))
	{
		if (*south_path != NULL)
			return (ft_put_error("argument(s) already for SO exist(s)"));
		if (line[2])
			return (ft_put_error("more arguments than expected for SO text."));
		if (!line[1])
			return (ft_put_error("invalid arguments for SO texture"));
		if (ft_check_path(line[1]))
			*south_path = line[1];
		printf("south texture %s\n", *south_path); // borrar
	}
	return (1);
}

int		ft_check_west_path(char **line, char **west_path)
{
	if (line[0] && (ft_strcmp(line[0], "WE") == 0))
	{
		if (*west_path != NULL)
			return (ft_put_error("argument(s) already for WE exist(s)"));
		if (line[2])
			return (ft_put_error("more arguments than expected for WE text."));
		if (!line[1])
			return (ft_put_error("invalid arguments WE texture"));
		if (ft_check_path(line[1]))
			*west_path = line[1];
		printf("west texture %s\n", *west_path); // borrar
	}
	return (1);
}

int		ft_check_east_path(char **line, char **east_path)
{
	if (line[0] && (ft_strcmp(line[0], "EA") == 0))
	{
		if (*east_path != NULL)
			return (ft_put_error("argument(s) already for EA exist(s)"));
		if (line[2])
			return (ft_put_error("more arguments than expected for EA text."));
		if (!line[1])
			return (ft_put_error("invalid arguments for EA texture"));
		if (ft_check_path(line[1]))
			*east_path = line[1];
		printf("east texture %s\n", *east_path); // borrar
	}
	return (1);
}

int		ft_check_sprite_path(char **line, char **sprite_path)
{
	if (line[0] && (ft_strcmp(line[0], "S") == 0))
	{
		if (*sprite_path != NULL)
			return (ft_put_error("argument(s) already for sprite exist(s)"));
		if (line[2])
			return (ft_put_error("more arguments than expected for texture"));
		if (!line[1])
			return (ft_put_error("invalid arguments for sprite texture"));
		if (ft_check_path(line[1]))
			*sprite_path = line[1];
		printf("sprite texture %s\n", *sprite_path); // borrar
	}
	return (1);
}