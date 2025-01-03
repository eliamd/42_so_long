/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 14:54:48 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/03 13:45:59 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static mlx_image_t	*load_texture_to_image(mlx_t *mlx, const char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(path);
	if (!texture)
		return (NULL);
	image = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	if (!image)
		return (NULL);
	if (!mlx_resize_image(image, TILE_SIZE, TILE_SIZE))
	{
		mlx_delete_image(mlx, image);
		return (NULL);
	}
	return (image);
}

int	init_textures(t_game *game)
{
	game->wall = load_texture_to_image(game->mlx, "assets/wall.png");
	game->floor = load_texture_to_image(game->mlx, "assets/floor.png");
	game->player = load_texture_to_image(game->mlx, "assets/player.png");
	game->collectible = load_texture_to_image(game->mlx,
			"assets/collectible.png");
	game->exit = load_texture_to_image(game->mlx, "assets/exit.png");
	if (!game->wall || !game->floor || !game->player
		|| !game->collectible || !game->exit)
		return (0);
	return (1);
}
