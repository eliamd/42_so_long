/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:12:44 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/03 13:47:19 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	render_tile(t_game *game, int x, int y)
{
	mlx_image_to_window(game->mlx, game->floor, x * TILE_SIZE, y * TILE_SIZE);
	if (game->map->grid[y][x] == WALL)
		mlx_image_to_window(game->mlx, game->wall,
			x * TILE_SIZE, y * TILE_SIZE);
	else if (game->map->grid[y][x] == COLLECTIBLE)
		mlx_image_to_window(game->mlx, game->collectible,
			x * TILE_SIZE, y * TILE_SIZE);
	else if (game->map->grid[y][x] == EXIT)
		mlx_image_to_window(game->mlx, game->exit,
			x * TILE_SIZE, y * TILE_SIZE);
}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	if (game->player->count > 0)
		mlx_delete_image(game->mlx, game->player);
	game->player = mlx_texture_to_image(game->mlx,
			mlx_load_png("assets/player.png"));
	if (!game->player || !mlx_resize_image(game->player, TILE_SIZE, TILE_SIZE))
		return ;
	y = -1;
	while (++y < game->map->height)
	{
		x = -1;
		while (++x < game->map->width)
			render_tile(game, x, y);
	}
	mlx_image_to_window(game->mlx, game->player,
		game->player_x * TILE_SIZE, game->player_y * TILE_SIZE);
}
