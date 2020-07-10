#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main(void)
{
    int fd;
    int ret;
    char *line;

    ret = 1;
    fd = open("valid_map.cub", O_RDONLY);
    //fd = 25;
    while (ret > 0)
    {
        ret = get_next_line(fd, &line);
        printf("[%d]-|%s\n", ret, line);
        free(line);
    }
   //while (1);
   //while(1) {} 
    return (1);
}