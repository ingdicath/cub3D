#include "cub3d.h"

int				main(int argc, char **argv)
{
	int			screenshot;
	t_game_file	game_file;

  	if (!ft_parsing(argc, argv, &game_file, &screenshot))
  		return (ft_put_error("Parsing failure"));
  	if (!ft_check_complete_elements(&game_file))
		return (ft_put_error("Scene map incomplete. Complete to continue"));
	if (screenshot)
		ft_take_screenshot(game_file);
	else
		ft_start_game(game_file);
	return (0);
}
