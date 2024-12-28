/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 23:05:16 by edetoh            #+#    #+#             */
/*   Updated: 2024/12/27 16:21:25 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("Error\nUsage: ./so_long map_path\n");
		return (1);
	}
	if (!init_game(&game, argv[1]))
	{
		ft_printf("Error\nFailed to initialize game\n");
		return (1);
	}
	mlx_key_hook(game.mlx, handle_input, &game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}
