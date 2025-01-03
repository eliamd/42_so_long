/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:00:22 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/03 11:58:02 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->grid)
	{
		write(1, "ici free_ma1\n", 14);
		ft_printf("map->height : %i\n", map->height);
		i = 0;
		while (i < map->height)
		{
			if (map->grid[i])
			{
				ft_printf("Freeing map->grid[%i] : %p\n", i, map->grid[i]);
				free(map->grid[i]);
				ft_printf("Freed map->grid[%i]\n", i);
				map->grid[i] = NULL;
			}
			i++;
		}
		write(1, "ici free_ma2\n", 14);
		free(map->grid);
		map->grid = NULL;
	}
	free(map);
}

void	cleanup_game(t_game *game)
{
	if (game->wall)
		mlx_delete_image(game->mlx, game->wall);
	if (game->floor)
		mlx_delete_image(game->mlx, game->floor);
	if (game->player)
		mlx_delete_image(game->mlx, game->player);
	if (game->collectible)
		mlx_delete_image(game->mlx, game->collectible);
	if (game->exit)
		mlx_delete_image(game->mlx, game->exit);
	if (game->map)
		free_map(game->map);
	if (game->mlx)
		mlx_terminate(game->mlx);
}
