/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:12:44 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/03 13:59:07 by edetoh           ###   ########.fr       */
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

static mlx_image_t	*load_texture_to_image(mlx_t *mlx, const char *path)
{
	static mlx_texture_t	*player_texture = NULL;

	if (!player_texture)
		player_texture = mlx_load_png(path);
	if (!player_texture)
		return (NULL);
	return (mlx_texture_to_image(mlx, player_texture));
}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	if (game->player->count > 0)
		mlx_delete_image(game->mlx, game->player);
	game->player = load_texture_to_image(game->mlx, "assets/player.png");
	if (!game->player)
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
