#include "cub3d.h"

void 		ft_put_pixel_bitmap(int fd, t_screen *screen)
{
	int		x;
	int		y;
	int     pos;
	char    *address;
	
	address = screen->win_data.address;
	y = screen->win_size.height - 1;  //porque tenemos que incluir el cero
	while (y >= 0)
	{
		x = 0;
		while (x < screen->win_size.width)
		{
			pos = y * screen->win_data.size_line +x *
					(screen->win_data.bits_per_pixel / EIGHT_BITS);
			write(fd, &address[pos], FOUR_BYTES);
			x++;
		}
		y--;
	}
}

void		ft_set_header_bitmap(int fd, t_screen *screen)
{
	int		file_size; 
	char	*file_type;

	file_type = "BM";
	file_size = screen->win_size.width * screen->win_size.height *
		(BITS_PER_PIXEL / EIGHT_BITS) + FINAL_IMAGE_SIZE;
	write(fd, file_type, TWO_BYTES);
	ft_write_int_bytes(fd, file_size);
	ft_write_char_zeros(fd, RESERVED_1);
	ft_write_char_zeros(fd, RESERVED_2);
	ft_write_int_bytes(fd, FINAL_IMAGE_SIZE);
	ft_write_int_bytes(fd, INFO_HEADER);
	ft_write_int_bytes(fd, screen->win_size.width);
	ft_write_int_bytes(fd, screen->win_size.height);
	ft_write_short_bytes(fd, PLANE);
	ft_write_short_bytes(fd, BITS_PER_PIXEL);
	ft_write_char_zeros(fd, COMPRESSION);
	ft_write_char_zeros(fd, IMAGE_SIZE);
	ft_write_char_zeros(fd, X_PPM);
	ft_write_char_zeros(fd, Y_PPM);
	ft_write_char_zeros(fd, TOTAL_COLORS);
	ft_write_char_zeros(fd, IMPORTANT_COLORS);
}

/*
** Flags
** 	- O_WRONLY: Open for writing only.
** 	- O_CREAT: the file shall be created if it does not exist.
** 	- O_TRUNC: truncating the file length to 0 if it does exist.
**
** mode_t: The Mode Bits for Access Permission
** It can set up with octal or with symbolic constants:
** 	1) 0777: Permissions read, write or execute, it should be in octal.
**	2) S_IRWXU: This is equivalent to ‘(S_IRUSR | S_IWUSR | S_IXUSR)’
*/

void ft_take_screenshot(t_game_file file)
{
	t_game game;

	int fd;

	fd = open(SCREENSHOT, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR); //preguntar si es full permission o solo lectura y escritura o es 755?
	if (fd < 0)
		ft_put_error("File screenshot cannot open");
	ft_set_game(file, &game);
	ft_set_header_bitmap(fd, &game.screen);
	ft_put_pixel_bitmap(fd, &game.screen);
	close(fd);
}