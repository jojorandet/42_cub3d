#include "cub3d.h"

static void	get_texture_position(t_main *main, t_texture texture, int wall_height, int start, int end, int texture_x, int screen_x)
{
	int				tex_pos_y;
	double			step;
	double			texture_pos;
	int				screen_y;
	int				color;

	screen_y = start;
	step = (double)texture.height / wall_height;
	texture_pos = (start - WIN_HEIGHT / 2 + wall_height / 2) * step;
	while (screen_y < end)
	{
		tex_pos_y = (int)texture_pos & (texture.height - 1);
		color = ((int *)texture.texture.addr)[texture.width * tex_pos_y + texture_x];
		put_pixel_to_image(main, screen_x, screen_y, color);
		texture_pos += step;
		screen_y++;
	}
}

static	int	get_texture_column(t_main *main, t_dda_struct *dda_struct, t_texture texture)
{
	double	width_pourcentage;
	double	width_pos_x;
	int		texture_coor_x;

	if(dda_struct->side == 0)
		width_pos_x = main->player.y + main->ray.dirY * dda_struct->perpwalldist;
	else
		width_pos_x = main->player.x + main->ray.dirX * dda_struct->perpwalldist;
	width_pourcentage = width_pos_x - floor(width_pos_x);
	texture_coor_x = (width_pourcentage * texture.width);
	if (dda_struct->side == 0 && main->ray.dirX > 0)
		texture_coor_x = texture.width - texture_coor_x - 1;
	if (dda_struct->side == 1 && main->ray.dirY < 0)
		texture_coor_x = texture.width - texture_coor_x - 1;
	return (texture_coor_x);
}

void	draw_wall(t_main *main, t_dda_struct *dda_struct, int x, t_texture texture)
{
	int			texture_coor_x;
	int			wall_height;
	int			draw_start;
	int			draw_end;

	texture_coor_x = get_texture_column(main, dda_struct, texture);
	wall_height = (int)(WIN_HEIGHT / dda_struct->perpwalldist);
	draw_start =  (WIN_HEIGHT / 2) - (wall_height / 2);
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (wall_height / 2) + (WIN_HEIGHT / 2);
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	get_texture_position(main, texture, wall_height, draw_start, draw_end, texture_coor_x, x);
}

t_texture	get_direction_for_texture(t_main *main, t_dda_struct *dda_struct)
{
	t_texture	texture;

	if (dda_struct->side == 0)
	{
		if (main->ray.dirX > 0)
			texture = main->wall.ea;
		else
			texture = main->wall.we;
	}
	else
	{
		if (main->ray.dirY < 0)
			texture = main->wall.no;
		else
			texture = main->wall.so;
	}
	return (texture);
}
