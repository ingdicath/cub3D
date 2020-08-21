#include "cub3d.h"

int				main(int argc, char **argv)
{
	int			screenshot;
	t_game_file	game_file;

	if (!ft_check_args(argc, argv, &screenshot))
		return (0);
	ft_reset_input(&game_file);
	if (!ft_read_file(argv[1], &game_file))
		return (0);
	if (!ft_check_complete_elements(&game_file))
		return (ft_put_error("Scene map incomplete. Complete to continue"));
	if (!ft_check_unique_orientation(&game_file.map))
		return (ft_put_error("check orientation in the map"));
	if (screenshot)
		ft_take_screenshot(game_file);
	else
		ft_start_game(game_file);
	return (0);
}
