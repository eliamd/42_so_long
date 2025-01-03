/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 13:23:56 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/03 13:24:16 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	allocate_grid(t_map *map)
{
	int	i;

	map->grid = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		return (0);
	i = 0;
	while (i <= map->height)
	{
		map->grid[i] = NULL;
		i++;
	}
	return (1);
}
