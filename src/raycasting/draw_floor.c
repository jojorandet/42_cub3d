#include "cub3d.h"

typedef struct	s_guide
{
	double	left_most_ray_x;
	double	right_most_ray_x;
	double	top_most_ray_y;
	double	bottom_most_ray_y;
	double	half_screen;
	double	distance_to_row;
	double	floor_stepX;
	double	floor_stepY;
	double	floor_x;
	double	floor_y;
	int		cellX;
	int		cellY;
	int		current_row;
}				t_guide;


static void	get_guide_info(t_main *main, t_guide *g, int y)
{
	t_player	*player;

	player = &main->player;
	g->current_row = y - g->half_screen;
	g->distance_to_row = g->half_screen / g->current_row;
	g->left_most_ray_x = player->dir_x - player->plane_x;
	g->right_most_ray_x = player->dir_x + player->plane_x;
	g->bottom_most_ray_y = player->dir_y + player->plane_y;
	g->top_most_ray_y = player->dir_y - player->plane_y;
	g->half_screen = (double)WIN_HEIGHT * 0.5;
	g->floor_stepX = g->distance_to_row * (g->right_most_ray_x - g->left_most_ray_x) / WIN_HEIGHT;
	g->floor_stepY = g->distance_to_row * (g->bottom_most_ray_y - g->top_most_ray_y) / WIN_HEIGHT;
	g->floor_x = player->x + g->distance_to_row * g->left_most_ray_x;
	g->floor_y = player->y + g->distance_to_row * g->top_most_ray_y;
}

void	draw_floor(t_main *main)
{
	int			y;
	int			x;
	t_guide		guide;
	t_texture	text_pos_x;

	y = 0;
	intialise_constants(main, &guide);
	while (y < WIN_HEIGHT)
	{
		get_guide_info(main, &guide, y);
		x = 0;
		while (x < WIN_WIDTH)
		{
			text_pos_x = (int)texture.
			x++;
		}
		y++;
	}
}
