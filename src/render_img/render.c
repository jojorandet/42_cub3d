
#include "cub3d.h"
#include "bonus.h"

static void	backgroud_color(t_main *main)
{
	int	x;
	int	y;
	int	midle;

	y = 0;
	midle = WIN_HEIGHT / 2;
	while (y <= midle)
	{
		x = 0;
		while (x <= WIN_WIDTH)
			put_pixel_to_image(main, x++, y, main->f_colour.value);
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x <= WIN_WIDTH)
			put_pixel_to_image(main, x++, y, main->c_colour.value);
		y++;
	}
}

int	render_next_frame(t_main *main)
{
	mlx_destroy_image(main->mlx_ptr, main->image.data_img);
	init_img(main);
	player_movement(main);
	backgroud_color(main);
	render_game(main);
	print_minimap(main);
	mlx_put_image_to_window(main->mlx_ptr, main->mlx_win,
		main->image.data_img, 0, 0);
	fps_counter(main);
	return (0);
}
