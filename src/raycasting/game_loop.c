
#include "cub3d.h"

void	render_game(t_main *main)
{
	int				x;
	t_dda_struct	dda_struct;
	t_texture		texture_direction;
	
	x = 0;
	while (x < WIN_WIDTH)
	{
		main->player.camera_x = 2 * x / (double)WIN_WIDTH - 1;
		main->ray.dirX = main->player.dir_x
			+ main->player.plane_x * main->player.camera_x;
		main->ray.dirY = main->player.dir_y
			+ main->player.plane_y * main->player.camera_x;
		digital_differential_analyzer(main, &dda_struct);
		//draw_floor;
		texture_direction = get_direction_for_texture(main, &dda_struct);
		draw_wall(main, &dda_struct, x, texture_direction);
		x++;
	}
}
