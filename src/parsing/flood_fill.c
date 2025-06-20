/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:28:19 by hdougoud          #+#    #+#             */
/*   Updated: 2025/06/20 14:20:32 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_parsing
{
	int		player;
	int		patern;
	char	**map;
}	t_parsing;

static bool	get_players(char **map, int *x, int *y, int *player)
{
	int	i;
	int	j;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (!ft_strchr("01NSWE' ", map[j][i]))
				return (print_error_and_message("unknown character"), false);
			if (map[j][i] == 'N' || map[j][i] == 'S'
				|| map[j][i] == 'W' || map[j][i] == 'E')
			{
				*x = i;
				*y = j;
				(*player)++;
			}
			i++;
		}
		j++;
	}
	return (true);
}

static bool	find_player_postion(char **map, int *x, int *y, int *player)
{
	if (!get_players(map, x, y, player))
		return (false);
	if (*player != 1)
	{
		if (*player < 1)
			print_error_and_message("No player found");
		else if (*player > 1)
			print_error_and_message("Too many players," \
				"it's a single-player game");
		return (false);
	}
	return (true);
}

static void	flood_fill(t_parsing *p, int x, int y)
{
	if (p->patern == 1)
		return ;
	if (x < 0 || y < 0 || p->map[y][x] == '\0' || p->map[y][x] == ' ')
	{
		p->patern = 1;
		return ;
	}
	if (p->map[y][x] == '1' || p->map[y][x] == 'V')
		return ;
	p->map[y][x] = 'V';
	flood_fill(p, x + 1, y);
	flood_fill(p, x, y + 1);
	flood_fill(p, x - 1, y);
	flood_fill(p, x, y - 1);
	flood_fill(p, x + 1, y + 1);
	flood_fill(p, x - 1, y - 1);
	flood_fill(p, x + 1, y - 1);
	flood_fill(p, x - 1, y + 1);
}

static char	**copy_map(char **map)
{
	int		i;
	int		j;
	char	**new_map;

	i = 0;
	j = 0;
	new_map = ft_calloc(count_map_height(map) + 1, sizeof(char *));
	if (!new_map)
		return (NULL);
	while (map[i])
	{
		new_map[j++] = ft_strdup(map[i++]);
		if (!new_map)
		{
			safe_free_tab((void ***)&new_map);
			return (NULL);
		}
	}
	return (new_map);
}

bool	is_map_valid(char **map)
{
	int			x;
	int			y;
	t_parsing	parsing;

	x = 0;
	y = 0;
	ft_bzero(&parsing, sizeof(t_parsing));
	if (!find_player_postion(map, &x, &y, &parsing.player))
		return (false);
	parsing.map = copy_map(map);
	if (!parsing.map)
		return (false);
	flood_fill(&parsing, x, y);
	if ((parsing.patern) == 1)
		return (print_error_and_message("Map : Wrong patern"), false);
	printf("map valid\n");
	return (true);
}
