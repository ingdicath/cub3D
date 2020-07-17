#include "../cub3d.h"
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(void)
{
    int 	fd;
    int 	ret;
    char 	*line;
  	char	**res;
  	int 	i;

    ret = 1;
    fd = open("valid_map.cub", O_RDONLY);
    while (ret > 0)
    {
        ret = get_next_line(fd, &line);
        // printf("[%d]-|%s\n", ret, line);
        res = ft_split(line,' ');
        i = 0;
        while (i < ft_count_words(line, ' '))
        {
			printf("%s_", res[i]);
			i++;
		}
		printf("\n");
	 	free(line);
	}
    return (1);
}


// int		main(void)
// {
// 	char 		*s;
// 	char		c;
// 	char		**res;
// 	size_t		i;
// 	i = 0;
// 	s = "     R         1090        1891        ";
// 	c = ' ';
// 	res = ft_split(s, c);
// 	while (i < ft_count_words(s, c))
// 	{
// 		printf("%s\n", res[i]);
// 		i++;
// 	}
// 	return (0);
// }