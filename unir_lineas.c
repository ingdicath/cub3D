#include "cub3d.h"
#include <stdio.h>

/*
static int ft_check_valid_elements(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != 'R' && line[i] != 'S' && line[i] != 'F' &&
			line[i] != 'C' && (line[0] != 'N' && line[1] != 'O') &&
			(line[0] != 'S' && line[1] != 'O') &&
			(line[0] != 'E' && line[1] != 'A') &&
			(line[0] != 'W' && line[1] != 'E'))
			return (0);
		i++;
	}
	return (1);
}






int main(int argc, char **argv)
{
	int ret;
	int fd;
	char *line;
	char **line_split;
	char *join_lines;
	int i;

	ret = 1;
	fd = open(argv[1], O_RDONLY);
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		// line_split = ft_split(line, '\n');
		if (ft_isemptyline(line))
				continue ;
		printf("|%d| - |%s|\n", ret, line);
		// printf("|%d| - |%s|\n", ret, *line_split);

		// i = 0;
		// if (ft_check_valid_elements(line) != 0)
		// 	printf(" valor %d\n", ft_check_valid_elements(line));
		// 	*line_split = ft_strjoin(line_split[i], line_split[i + 1]);
		// // printf("|%d| - |%s|\n", ret, *join_lines);
		i++;
		free (line);
	}

	//ft_check_valid_char(line)
	return (1);
}
*/

int fibo(int n)
{
	if (n == 0)
		return (0);
	if (n == 1 || n == 2)
		return (1);
	return (fibo(n-1) + fibo(n-2));
}

int main(void)
{
	int n;
	int i;

	i = 0;
	n = 6;
	while (i < n)
	{
		printf("Res is: %d\n", fibo(n));
		printf("Res is: %d\n", fibo(n-1));
		printf("Res is: %d\n", fibo(n-2));
		i++;
	}
	
	
	return 0;
}

