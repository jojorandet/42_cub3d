
#include "cub3d.h"

static void	player_rotation(t_main *main)
{
	if (main->keys.left || main->keys.right)
	{
		double	old_dir_x;
		double	rotation_speed;
		double	old_plane_x;

		if (main->keys.left)
			rotation_speed = -ROTATION_SPEED; // for using only one function
		if (main->keys.right)
			rotation_speed = ROTATION_SPEED; // for using only one function
		old_dir_x = main->player.dir_x;
		main->player.dir_x = main->player.dir_x * cos(rotation_speed) - main->player.dir_y * sin(rotation_speed);
		main->player.dir_y = old_dir_x * sin(rotation_speed) + main->player.dir_y * cos(rotation_speed);
		old_plane_x = main->player.plane_x;
		main->player.plane_x = main->player.plane_x * cos(rotation_speed) - main->player.plane_y * sin(rotation_speed);
		main->player.plane_y = old_plane_x * sin(rotation_speed) + main->player.plane_y * cos(rotation_speed);
		main->player.angle = atan2(main->player.dir_y, main->player.dir_x); //update plaer_angle for minimap
	}
}

static void	valid_next_movement(t_main *main, double x, double y)
{
	if (main->map_struct.map[(int)trunc(y)][(int)trunc(x)] == '0')
	{
		main->player.x = x;
		main->player.y = y;
	}
}

static void	player_right_and_left(t_main *main)
{
	double	new_x;
	double	new_y;

	if (main->keys.d == 1)
	{
		new_x = main->player.x + (main->player.plane_x * PLAYER_SPEED);
		new_y = main->player.y + (main->player.plane_y * PLAYER_SPEED);
		valid_next_movement(main, new_x, new_y);
	}
	if (main->keys.a == 1)
	{
		new_x = main->player.x - (main->player.plane_x * PLAYER_SPEED);
		new_y = main->player.y - (main->player.plane_y * PLAYER_SPEED);
		valid_next_movement(main, new_x, new_y);
	}
}

static void	player_up_and_down(t_main *main)
{
	double	new_x;
	double	new_y;

	if (main->keys.w == 1)
	{
		new_x = main->player.x + (main->player.dir_x * PLAYER_SPEED);
		new_y = main->player.y + (main->player.dir_y * PLAYER_SPEED);
		valid_next_movement(main, new_x, new_y);
	}
	if (main->keys.s == 1)
	{
		new_x = main->player.x - (main->player.dir_x * PLAYER_SPEED);
		new_y = main->player.y - (main->player.dir_y * PLAYER_SPEED);
		valid_next_movement(main, new_x, new_y);
	}
}

void	player_movement(t_main *main)
{
	player_up_and_down(main);
	player_right_and_left(main);
	player_rotation(main);
}