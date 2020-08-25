/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   screenshot.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 09:53:36 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/25 14:03:28 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** Flags
** 	- O_WRONLY: Open for writing only.
** 	- O_CREAT: the file shall be created if it does not exist.
** 	- O_TRUNC: truncating the file length to 0 if it does exist.
**
** mode_t: The Mode Bits for Access Permission
** It can set up with octal or with symbolic constants:
** 	1) 0644: Permissions read, write or execute, it should be in octal.
**	2) S_IRWXU: This is equivalent to ‘(S_IRUSR | S_IWUSR | S_IXUSR)’
*/

void		ft_take_screenshot(t_game_file file)
{
	int		fd;
	t_game	game;

	fd = open(SCREENSHOT, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		ft_put_error("File screenshot cannot open");
	ft_set_game(file, &game, 1);
	ft_set_header_bitmap(fd, &game.screen);
	ft_put_pixel_bitmap(fd, &game.screen);
	close(fd);
}

void		ft_set_header_bitmap(int fd, t_screen *screen)
{
	int		file_size;
	char	*file_type;

	file_type = "BM";
	file_size = screen->resolution.width * screen->resolution.height *
		(BITS_PER_PIXEL / EIGHT_BITS) + FINAL_IMAGE_SIZE;
	write(fd, file_type, TWO_BYTES);
	ft_write_int_bytes(fd, file_size);
	ft_write_char_zeros(fd, RESERVED_1);
	ft_write_char_zeros(fd, RESERVED_2);
	ft_write_int_bytes(fd, FINAL_IMAGE_SIZE);
	ft_write_int_bytes(fd, INFO_HEADER);
	ft_write_int_bytes(fd, screen->resolution.width);
	ft_write_int_bytes(fd, screen->resolution.height);
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
** y = screen->resolution.height - 1, '-1' is to include the position zero
**
*/

void		ft_put_pixel_bitmap(int fd, t_screen *screen)
{
	int		x;
	int		y;
	int		pos;
	char	*address;

	address = screen->win_data.address;
	y = screen->resolution.height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < screen->resolution.width)
		{
			pos = y * screen->win_data.size_line + x *
					(screen->win_data.bits_per_pixel / EIGHT_BITS);
			write(fd, &address[pos], FOUR_BYTES);
			x++;
		}
		y--;
	}
}
