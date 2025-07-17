#include "cub3d.h"

typedef struct	s_guide
{
	double	left_most_ray_x;
	double	right_most_ray_x;
	double	top_most_ray_y;
	double	bottom_most_ray_y;
	double	half_screen;
	double	distance_to_floor;
	double	floor_stepX;
	double	floor_stepY;
	double	floor_x;
	double	floor_y;
}				t_guide;

static void	get_proportion_ratios(t_guide *guide, double dist_to_row)
{
	guide->floor_stepX = dist_to_row * (guide->right_most_ray_x - guide->left_most_ray_x) / WIN_HEIGHT;
	guide->floor_stepY = dist_to_row * (guide->bottom_most_ray_y - guide->top_most_ray_y) / WIN_HEIGHT;
}

static void	intialise_constants(t_main *main, t_guide *guide)
{
	t_player	*player;

	player = &main->player;
	guide->left_most_ray_x = player->x - player->plane_x;
	guide->right_most_ray_x = player->x + player->plane_x;
	guide->bottom_most_ray_y = player->y + player->plane_y;
	guide->top_most_ray_y = player->y - player->plane_y;
	guide->half_screen = (double)WIN_HEIGHT * 0.5;
}

void	draw_floor(t_main *main)
{
	int			y;
	int			current_row;
	double		distance_to_row;
	t_guide		guide;

	y = 0;
	intialise_constants(main, &guide);
	while (y < WIN_HEIGHT)
	{
		current_row = y - guide.half_screen;
		distance_to_row = current_row / guide.half_screen;
		get_proportion_ratios(&guide, distance_to_row);

		y++;
	}
}
