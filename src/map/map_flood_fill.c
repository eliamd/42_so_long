/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_flood_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:00:00 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/03 16:03:20 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

char	**duplicate_grid(t_map *map)
{
	char	**grid;
	int		i;

	grid = (char **)malloc(sizeof(char *) * (map->height));
	if (!grid)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		grid[i] = ft_strdup(map->grid[i]);
		if (!grid[i])
		{
			while (--i >= 0)
				free(grid[i]);
			free(grid);
			return (NULL);
		}
		i++;
	}
	return (grid);
}

static void	flood_fill(char **grid, t_point size, t_point cur, int *collect)
{
	if (cur.x < 0 || cur.x >= size.x || cur.y < 0 || cur.y >= size.y
		|| grid[cur.y][cur.x] == WALL || grid[cur.y][cur.x] == 'V')
		return ;
	if (grid[cur.y][cur.x] == COLLECTIBLE)
		(*collect)++;
	grid[cur.y][cur.x] = 'V';
	flood_fill(grid, size, (t_point){cur.x + 1, cur.y}, collect);
	flood_fill(grid, size, (t_point){cur.x - 1, cur.y}, collect);
	flood_fill(grid, size, (t_point){cur.x, cur.y + 1}, collect);
	flood_fill(grid, size, (t_point){cur.x, cur.y - 1}, collect);
}

static t_point	find_player(t_map *map)
{
	t_point	pos;

	pos.y = 0;
	while (pos.y < map->height)
	{
		pos.x = 0;
		while (pos.x < map->width)
		{
			if (map->grid[pos.y][pos.x] == PLAYER)
				return (pos);
			pos.x++;
		}
		pos.y++;
	}
	return ((t_point){-1, -1});
}

int	is_map_solvable(t_map *map)
{
	char	**temp_grid;
	t_point	size;
	t_point	start;
	int		collectibles;

	temp_grid = duplicate_grid(map);
	if (!temp_grid)
		return (0);
	size = (t_point){map->width, map->height};
	start = find_player(map);
	collectibles = 0;
	flood_fill(temp_grid, size, start, &collectibles);
	while (map->height--)
		free(temp_grid[map->height]);
	free(temp_grid);
	if (collectibles != map->collectibles)
		return (0);
	return (1);
}
