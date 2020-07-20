#include "../cub3d.h"
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  int 	fd;
  int 	ret;
  char 	*line;
  char	**res;
  int 	i;

  ret = 1;
  fd = open(argv[1], O_RDONLY);
  if (argc < 2)
    return(ft_put_error("at least one argument was expected"));
  while (ret > 0)
  {
    ret = get_next_line(fd, &line);
    if (ret < 0)
      return(ft_put_error("File not found"));
    res = ft_split(line,' ');
    i = 0;
    while (i < ft_count_words(line, ' '))
    {
      ft_putstr(res[i]);
      ft_putstr(",");
      i++;
    }
    ft_putstr("\n");
    free(line);
  }
  return (1);
}


// int main(void)
// {
//     int 	fd;
//     int 	ret;
//     char 	*line;
//   	char	**res;
//   	int 	i;

//     ret = 1;
//     fd = open("valid_map.cub", O_RDONLY);
//     while (ret > 0)
//     {
//         ret = get_next_line(fd, &line);
//         // printf("[%d]-|%s\n", ret, line);
//         res = ft_split(line,' ');
//         i = 0;
//         while (i < ft_count_words(line, ' '))
//         {
// 			printf("%s,", res[i]);
// 			i++;
// 		}
// 		printf("\n");
// 	 	free(line);
// 	}
//     return (1);
// }


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