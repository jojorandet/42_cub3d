/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:36:06 by hdougoud          #+#    #+#             */
/*   Updated: 2025/07/18 10:37:01 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_perpwall_dist(t_dda_struct *dda)
{
	if (dda->side == 0)
		dda->perpwalldist = (dda->sideDistX - dda->delta_x);
	else
		dda->perpwalldist = (dda->sideDistY - dda->delta_y);
}

/**
 * @param sideDistX est un vecteur que l'on multiplie avec un scalaire !
 * @param sideDisty est un vecteur que l'on multiplie avec un scalaire !
 * @brief On augmente le vecteur SideDistX ou SideDistY selon l'angle du vecteur
 */
// t_vec2	vector;
// continue tant que mur n'est pas hit
static void	dda_main_loop(t_main *main, t_dda_struct *dda)
{
	while (dda->hit == 0)
	{
		if (dda->sideDistX < dda->sideDistY)
		{
			dda->sideDistX += dda->delta_x;
			dda->mapX += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->sideDistY += dda->delta_y;
			dda->mapY += dda->step_y;
			dda->side = 1;
		}
		if (main->map_struct.map[(int)dda->mapY][(int)dda->mapX] != '0')
		{
			dda->hit = 1;
		}
	}
}

// si le rayon est dans la partie gauche de l'ecrann, step x sera -1
static void	get_step_and_sidedist(t_main *main, t_dda_struct *dda)
{
	if (main->ray.dirX < 0)
	{
		dda->step_x = -1;
		dda->sideDistX = (main->player.x - dda->mapX) * dda->delta_x;
	}
	else
	{
		dda->step_x = 1;
		dda->sideDistX = (dda->mapX + 1.0 - main->player.x) * dda->delta_x;
	}
	if (main->ray.dirY < 0)
	{
		dda->step_y = -1;
		dda->sideDistY = (main->player.y - dda->mapY) * dda->delta_y;
	}
	else
	{
		dda->step_y = 1;
		dda->sideDistY = (dda->mapY + 1.0 - main->player.y) * dda->delta_y;
	}
}

void	digital_differential_analyzer(t_main *main, t_dda_struct *dda_struct)
{
	ft_bzero(dda_struct, sizeof(t_dda_struct));
	dda_struct->mapX = main->player.x;
	dda_struct->mapY = main->player.y;
	if (main->ray.dirX == 0)
		dda_struct->delta_x = pow(10, 30);
	else
		dda_struct->delta_x = fabs(1 / main->ray.dirX);
	if (main->ray.dirY == 0)
		dda_struct->delta_y = pow(10, 30);
	else
		dda_struct->delta_y = fabs(1 / main->ray.dirY);
	dda_struct->hit = 0;
	get_step_and_sidedist(main, dda_struct);
	dda_main_loop(main, dda_struct);
	get_perpwall_dist(dda_struct);
}
