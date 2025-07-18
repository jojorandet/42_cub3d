/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:42:48 by hdougoud          #+#    #+#             */
/*   Updated: 2025/07/18 10:43:32 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	flood_fill(t_parsing *p, int x, int y)
{
	if (p->patern == 1)
		return ;
	if (x < 0 || y < 0 || y >= p->map_height || x >= p->map_width
		|| p->map[y][x] == '\0' || p->map[y][x] == ' ')
	{
		p->patern = 1;
		return ;
	}
	if (p->map[y][x] == '1' || p->map[y][x] == 'V')
		return ;
	p->map[y][x] = 'V';
	if (p->patern == 1)
		return ;
	flood_fill(p, x + 1, y);
	flood_fill(p, x, y + 1);
	flood_fill(p, x - 1, y);
	flood_fill(p, x, y - 1);
	flood_fill(p, x + 1, y + 1);
	flood_fill(p, x - 1, y - 1);
	flood_fill(p, x + 1, y - 1);
	flood_fill(p, x - 1, y + 1);
}

static char	**copy_map(char **map, t_parsing *parsing)
{
	int		i;
	int		j;
	char	**new_map;

	i = 0;
	j = 0;
	new_map = ft_calloc(parsing->map_height + 1, sizeof(char *));
	if (!new_map)
		return (NULL);
	while (map[i])
	{
		new_map[j] = max_strdup(map[i++], parsing->map_width);
		if (!new_map[j])
		{
			safe_free_tab((void ***)&new_map);
			return (NULL);
		}
		j++;
	}
	return (new_map);
}

void	is_map_valid(t_main *main)
{
	int			x;
	int			y;
	t_parsing	parsing;

	x = 0;
	y = 0;
	if (main->map_struct.height == 0 || main->map_struct.width == 0)
		exit_cub3d(main, "No map, please input a valid map.");
	if (main->map_struct.height < 3 || main->map_struct.width < 3)
		exit_cub3d(main, "Map too small, must be 3 x 3 minimum.");
	ft_bzero(&parsing, sizeof(t_parsing));
	if (!find_player_position(main, &x, &y, &parsing.player))
		exit_cub3d(main, "Player not found.");
	parsing.map_height = main->map_struct.height;
	parsing.map_width = main->map_struct.width;
	parsing.map = copy_map(main->map_struct.map, &parsing);
	if (!parsing.map)
		exit_cub3d(main, "Map could not be copied in is_map_valid.");
	flood_fill(&parsing, x, y);
	safe_free_tab((void ***)&parsing.map);
	if ((parsing.patern) == 1)
		exit_cub3d(main, "Map invalid");
}
