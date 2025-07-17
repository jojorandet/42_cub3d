
#include "cub3d.h"

void	free_all_pointer_arrays(t_main *main)
{
	if (main->map_struct.map)
		free_string_array(&main->map_struct.map);
	if (main->file_content)
		free_string_array(&main->file_content);
	if (main->id_and_info)
		free_string_array(&main->id_and_info);
}

void	free_mlx_pointers(t_main *main)
{
	if (main->image.data_img)
			mlx_destroy_image(main->mlx_ptr, main->image.data_img);
	if (main->mlx_win)
	{
		mlx_destroy_window(main->mlx_ptr, main->mlx_win);
		main->mlx_win = NULL;
	}
	if (main->os == LINUX)
	{
		if (main->mlx_ptr)
		{
			mlx_destroy_display(main->mlx_ptr);
			free(main->mlx_ptr);
		}
	}
	if (main->os == MACOS)
	{
		if (main->mlx_ptr)
			free(main->mlx_ptr);
	}
}

void	exit_cub3d(t_main *main, char *error_message)
{
	if (main)
	{
		free_all_pointer_arrays(main);
		free_mlx_pointers(main);
	}
	if (error_message)
	{
		print_error_and_message(error_message);
		if (errno)
			perror("Cub3d: ");
		exit(1);
	}
	exit(0);
}

int	handle_destroy(t_main *main)
{
	exit_cub3d(main, 0);
	return (0);
}
