// se necesitan 2 funciones 
/*
1. imprime el header
2. imprime el body
3. enum de valores de tamano del metadata sugerido header_metadata

*/
// fd, resolution
void		file_header_bmp(int fd, int width, int height)
{
	int		size;
	int		first_pix;
	int		headersize;
	short	plain;
	short	bpp;

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
}


void		info_header_bmp(int fd, int width, int height)
{
	int		y;
	int		x;
	int		i;
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