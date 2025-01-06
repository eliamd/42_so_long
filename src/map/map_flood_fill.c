/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_flood_fill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:00:00 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/06 13:49:15 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	flood_fill(char **grid, t_point size, t_point cur, int *collect)
{
	if (cur.x < 0 || cur.x >= size.x || cur.y < 0 || cur.y >= size.y
		|| grid[cur.y][cur.x] == WALL || grid[cur.y][cur.x] == EXIT \
		|| grid[cur.y][cur.x] == 'V')
		return ;
	if (grid[cur.y][cur.x] == COLLECTIBLE)
		(*collect)++;
	grid[cur.y][cur.x] = 'V';
	flood_fill(grid, size, (t_point){cur.x + 1, cur.y}, collect);
	flood_fill(grid, size, (t_point){cur.x - 1, cur.y}, collect);
	flood_fill(grid, size, (t_point){cur.x, cur.y + 1}, collect);
	flood_fill(grid, size, (t_point){cur.x, cur.y - 1}, collect);
}

static void	flood_fill_exi(char **grid, t_point size, t_point cur, int *collect)
{
	if (cur.x < 0 || cur.x >= size.x || cur.y < 0 || cur.y >= size.y
		|| grid[cur.y][cur.x] == WALL \
		|| grid[cur.y][cur.x] == 'V')
		return ;
	if (grid[cur.y][cur.x] == EXIT)
		(*collect)++;
	grid[cur.y][cur.x] = 'V';
	flood_fill_exi(grid, size, (t_point){cur.x + 1, cur.y}, collect);
	flood_fill_exi(grid, size, (t_point){cur.x - 1, cur.y}, collect);
	flood_fill_exi(grid, size, (t_point){cur.x, cur.y + 1}, collect);
	flood_fill_exi(grid, size, (t_point){cur.x, cur.y - 1}, collect);
}

int	perform_flood_fill(t_map *map, char **temp_grid, int *collect, int is_exit)
{
	t_point	size;
	t_point	start;
	int		tmp;

	size = (t_point){map->width, map->height};
	start = find_player(map);
	if (is_exit)
		flood_fill_exi(temp_grid, size, start, collect);
	else
		flood_fill(temp_grid, size, start, collect);
	tmp = map->height;
	while (tmp--)
		free(temp_grid[tmp]);
	free(temp_grid);
	return (1);
}

int	is_map_solvable(t_map *map)
{
	char	**temp_grid;
	t_point	collectibles;
	int		tmp;

	tmp = map->height;
	temp_grid = duplicate_grid(map);
	if (!temp_grid)
		return (0);
	collectibles = (t_point){0, 0};
	if (!perform_flood_fill(map, temp_grid, &collectibles.x, 0))
		return (0);
	temp_grid = duplicate_grid(map);
	if (!temp_grid)
		return (0);
	if (!perform_flood_fill(map, temp_grid, &collectibles.y, 1))
		return (0);
	if (collectibles.x != map->collectibles || collectibles.y != map->exit)
		return (0);
	return (1);
}
