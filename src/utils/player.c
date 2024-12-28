/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 00:25:37 by edetoh            #+#    #+#             */
/*   Updated: 2024/12/27 16:21:24 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	can_move(t_game *game, int new_x, int new_y)
{
	char	next_pos;

	next_pos = game->map->grid[new_y][new_x];
	if (next_pos == WALL)
		return (0);
	if (next_pos == EXIT && game->collected != game->map->collectibles)
		return (0);
	return (1);
}

static void	handle_collectible(t_game *game, int new_x, int new_y)
{
	size_t	i;

	game->collected++;
	game->map->grid[new_y][new_x] = EMPTY;
	i = 0;
	while (i < game->collectible->count)
	{
		if (game->collectible->instances[i].x == new_x * TILE_SIZE
			&& game->collectible->instances[i].y == new_y * TILE_SIZE)
		{
			game->collectible->instances[i].enabled = false;
			break ;
		}
		i++;
	}
}

static void	update_player_position(t_game *game, int new_x, int new_y)
{
	game->map->grid[game->player_y][game->player_x] = EMPTY;
	game->map->grid[new_y][new_x] = PLAYER;
	game->player->instances[0].x = new_x * TILE_SIZE;
	game->player->instances[0].y = new_y * TILE_SIZE;
	game->player_x = new_x;
	game->player_y = new_y;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
}

void	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	if (!can_move(game, new_x, new_y))
		return ;
	if (game->map->grid[new_y][new_x] == COLLECTIBLE)
		handle_collectible(game, new_x, new_y);
	else if (game->map->grid[new_y][new_x] == EXIT
		&& game->collected == game->map->collectibles)
	{
		ft_printf("Congratulations! You won in %d moves!\n", game->moves + 1);
		mlx_close_window(game->mlx);
		return ;
	}
	update_player_position(game, new_x, new_y);
}
