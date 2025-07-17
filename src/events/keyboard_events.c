
#include "cub3d.h"

static int	key_pressed(int keycode, t_main *main)
{
	if (keycode == K_W)
		main->keys.w = 1;
	if (keycode == K_A)
		main->keys.a = 1;
	if (keycode == K_S)
		main->keys.s = 1;
	if (keycode == K_D)
		main->keys.d = 1;
	if (keycode == K_G)
		main->keys.g = !main->keys.g;
	if (keycode == K_M)
		main->keys.m = !main->keys.m;
	if (keycode == K_LEFT)
		main->keys.left = 1;
	if (keycode == K_RIGHT)
		main->keys.right = 1;
	if (keycode == K_ESCP)
		exit_cub3d(main, 0);
	if (main->debug.last_keycode != keycode)
		printf("keycode : %d\n", keycode);
	main->debug.last_keycode = keycode;
	return (1);
}

static int	key_released(int keycode, t_main *main)
{
	if (keycode == K_W)
		main->keys.w = 0;
	if (keycode == K_A)
		main->keys.a = 0;
	if (keycode == K_S)
		main->keys.s = 0;
	if (keycode == K_D)
		main->keys.d = 0;
	if (keycode == K_LEFT)
		main->keys.left = 0;
	if (keycode == K_RIGHT)
		main->keys.right = 0;
	return (0);
}

void	init_keyboard_events(t_main *main)
{
	mlx_hook(main->mlx_win, ON_KEYDOWN, 1L << 0, key_pressed, main);
	mlx_hook(main->mlx_win, ON_KEYUP, 1L << 1, key_released, main);
}
