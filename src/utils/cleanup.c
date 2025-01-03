/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:00:22 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/03 10:42:35 by edetoh           ###   ########.fr       */
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
		i = 0;
		while (i < map->height)
			free(map->grid[i++]);
		free(map->grid);
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
