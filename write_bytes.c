#include "cub3d.h"

static void ft_write_int_bytes(int fd, int param)
{
	write(fd, &param, FOUR_BYTES);
}

static void ft_write_short_bytes(int fd, int param)
{	
	write(fd, &param, TWO_BYTES);
}

static void ft_write_char_zeros(int fd, int times)
{
	int i; 

	i = 0;
	while (i < times)
	{
		write(fd, "\0", ONE_BYTE);
		i++;
	}
}
