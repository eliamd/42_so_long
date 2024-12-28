/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:03:39 by edetoh            #+#    #+#             */
/*   Updated: 2024/12/27 16:30:23 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	init_mlx(t_game *game)
{
	game->mlx = mlx_init(game->map->width * TILE_SIZE,
			game->map->height * TILE_SIZE, "so_long", true);
	if (!game->mlx)
	{
		free_map(game->map);
		ft_putstr_fd(ERR_INIT_MLX, 2);
		return (0);
	}
	return (1);
}

static int	init_map_struct(t_game *game, char *map_path)
{
	game->map = (t_map *)malloc(sizeof(t_map));
	if (!game->map)
	{
		ft_putstr_fd(ERR_MAP_MISSING, 2);
		return (0);
	}
	ft_memset(game->map, 0, sizeof(t_map));
	if (!parse_map(game, map_path) || !validate_map(game->map))
	{
		free_map(game->map);
		return (0);
	}
	return (1);
}

static void	init_game_values(t_game *game)
{
	int	y;
	int	x;

	game->collected = 0;
	game->moves = 0;
	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			if (game->map->grid[y][x] == PLAYER)
			{
				game->player_x = x;
				game->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

int	init_game(t_game *game, char *map_path)
{
	if (!check_map_extension(map_path))
	{
		ft_putstr_fd(ERR_MAP_EXT, 2);
		return (0);
	}
	ft_memset(game, 0, sizeof(t_game));
	if (!init_map_struct(game, map_path))
		return (0);
	if (!init_mlx(game))
		return (0);
	if (!init_textures(game))
	{
		cleanup_game(game);
		ft_putstr_fd(ERR_LOAD_TEXTURES, 2);
		return (0);
	}
	init_game_values(game);
	render_map(game);
	return (1);
}
