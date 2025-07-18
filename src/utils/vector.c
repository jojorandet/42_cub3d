/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:35:57 by hdougoud          #+#    #+#             */
/*   Updated: 2025/07/18 10:36:54 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

t_vec2	get_vector(double x1, double y1, double x2, double y2)
{
	t_vec2	vector;

	vector.x = x2 - x1;
	vector.y = y2 - y1;
	return (vector);
}

double	get_vector_norm(t_vec2 vec1, t_vec2 vec2)
{
	return (sqrt((pow(vec2.x - vec1.x, 2) + pow(vec2.y - vec1.y, 2))));
}
