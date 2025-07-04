
#include "cub3d.h"

static bool	arguments_are_valid(int argc, char **argv)
{
	if (argc != 2)
	{
		print_error_and_message("Please give only one file as input.\n");
		return (false);
	}
	if (!cub_extension_is_valid(argv[1], 3))
	{
		print_error_and_message(".cub extenssion is missing.\n");
		return (false);
	}
	return (true);
}

static void	init_cub3d(t_main *main)
{
	int	x;
	int	y;

	x = WIN_WIDTH;
	y = WIN_HEIGHT;
	main->mlx_ptr = mlx_init();
	if (!main->mlx_ptr)
		exit_cub3d(main, "Mlx init failed.");
	main->mlx_win = mlx_new_window(main->mlx_ptr, x, y, "Cub3d");
	if (!main->mlx_win)
		exit_cub3d(main, "Mlx window failed");
	mlx_hook(main->mlx_win, 17, 0, handle_destroy, main);
	init_img(main);
}

int	main(int argc, char **argv)
{
	t_main	main;

	ft_bzero(&main, sizeof(t_main));
	if (!arguments_are_valid(argc, argv))
		return (EXIT_FAILURE);
	init_cub3d(&main);
	parsing(&main, argv[1]);
	init_keyboard_events(&main);
	mlx_loop_hook(main.mlx_ptr, render_next_frame, &main);
	mlx_loop(main.mlx_ptr);
	return (0);
}
