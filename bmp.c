// se necesitan 2 funciones 
/*
1. imprime el header
2. imprime el body
3. enum de valores de tamano del metadata sugerido header_metadata

*/
// fd, resolution

#include "cub3d.h"
#include <stdio.h>

void		ft_set_header_bmp(int fd, t_board board)
{
	int		file_size;
	int 	pixel_data_offset;
	int 	plane;
	int		bits_per_pixel;
	int		padding;
	char	*file_type;
	char	*reserved_space;

	file_type = "BM";
	file_size = board.resolution.width * board.resolution.height *
		(BITS_PER_PIXEL / 8) + FINAL_IMAGE_SIZE;
	pixel_data_offset = FINAL_IMAGE_SIZE;
	reserved_space = "\0\0\0\0";
	plane = PLANE;
	bits_per_pixel = BITS_PER_PIXEL;
	padding = 0;
	write(fd, file_type, TWO_BYTES);
	write(fd, &file_size, FOUR_BYTES);
	write(fd, reserved_space, FOUR_BYTES);
	write(fd, &pixel_data_offset, FOUR_BYTES);
	write(fd, &board.resolution.width, FOUR_BYTES);
	write(fd, &board.resolution.height, FOUR_BYTES);
	write(fd, &plane, TWO_BYTES);
	write(fd, &bits_per_pixel, TWO_BYTES);
	while (padding < BMP_PIXELS)
	{
		write(fd, "\0", 1);
		padding++;
	}
}

void ft_put_pixel_bmp(int fd, t_board board)
{
	int x;
	int y;
	char *dest;

	y = board.resolution.height;
	while (y > 0)
	{
		x = 0;
		while (x < board.resolution.width)
		{
			dest = board.win_data.address + (y * board.win_data.size_line + x *
				(board.win_data.bits_per_pixel / 8));
			write(fd, dest, FOUR_BYTES);
			// write(fd, &dest[board.resolution.height * board.win_data.size_line + x * 4], FOUR_BYTES);
			x++;
		}
		y--;
	}
}




	headersize = 40; // enum value header size
	plain = 1; // enum value
	bpp = 32; // constante, o del board
	first_pix = 54; // constante, tamano del file header size +  info header size
	size = height * width * 4 + 54; // bpp / 8 (8 bits)
	
	// char * type = "BM";
	write(fd, "BM", 2); 
	
	write(fd, &size, 4);
	
	// char * reserved_space = "\0\0\0\0";
	write(fd, "\0\0\0\0", 4); // 4_BYTES
	write(fd, &first_pix, 4);
	write(fd, &headersize, 4);
	write(fd, &width, 4);
	write(fd, &height, 4);
	write(fd, &plain, 2); // 2_BYTES
	write(fd, &bpp, 2);
	
	// pading = 0  pading < 24, bmp pixels
	while (plain <= 24)
	{
		write(fd, "\0", 1); 1_BYTE
		plain++;
	}



void		info_header_bmp(int fd, int width, int height)
{
	int		y;
	int		x;
	char	*dest;

	i = 0;
	y = base->read.render_y;

	while (y > 0)
	{
		x = 0;
		while (x < base->read.render_x)
		{
			dest = mlx->addr + (y * mlx->line_length + x * (mlx->bpp / 8));
			//pixelbuffer[i] = *(unsigned int*)dest;
			write(fd, &addr[height * build->img.line_length + x * 4], 4); //4 es la cantida de pixeles a imprimin
			x++;
		}
		y--;
	}
	return (pixelbuffer);
}


/*

int main (void)
{
	int		file_size;
	int 	pixel_data_offset;
	char	*file_type;
	int width = 1920;
	t_bitmap *bmp;

	file_size = FINAL_IMAGE_SIZE;
	// bmp->file_header.signature = "BM";
	file_type = "BM";
	// pixel_data_offset = HEADER_SIZE;
	pixel_data_offset = 54;

	// write(1, bmp->file_header.signature, TWO_BYTES);
	write(1, file_type, TWO_BYTES);
	write(1, "\n", 1);
	write(1, "\n", 1);
	write(1, &width, FOUR_BYTES);
	write(1, "\n", 1);
	write(1, "hola", 4);
	write(1, "\n", 1);
	write(1, &pixel_data_offset, 4);
	// write(1, (int *)HEADER_SIZE, 4);

	return (0);
}
*/

