/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_flood_fill_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:00:00 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/06 13:04:15 by edetoh           ###   ########.fr       */
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

t_point	find_player(t_map *map)
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
