/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:13:01 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/03 11:02:41 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	check_map_extension(char *filename)
{
	char	*dot;

	if (!filename)
		return (0);
	dot = ft_strrchr(filename, '.');
	if (!dot || ft_strncmp(dot, ".ber", 5) != 0)
		return (0);
	return (1);
}

int	check_map_walls(t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->width)
		if (map->grid[0][i] != WALL || map->grid[map->height - 1][i] != WALL)
			return (0);
	i = -1;
	while (++i < map->height)
		if (map->grid[i][0] != WALL || map->grid[i][map->width - 1] != WALL)
			return (0);
	return (1);
}

int	check_map_elements(t_map *map)
{
	int	x;
	int	y;

	map->player = 0;
	map->exit = 0;
	map->collectibles = 0;
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (!ft_strchr("01CEP", map->grid[y][x]))
				return (0);
			if (map->grid[y][x] == PLAYER)
				map->player++;
			else if (map->grid[y][x] == EXIT)
				map->exit++;
			else if (map->grid[y][x] == COLLECTIBLE)
				map->collectibles++;
		}
	}
	return (map->player == 1 && map->exit == 1 && map->collectibles > 0);
}

int	validate_map(t_map *map)
{
	return (check_map_elements(map) && check_map_walls(map));
}
