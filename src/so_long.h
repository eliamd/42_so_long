/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 22:59:47 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/03 11:01:31 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../42_libft-mylibft/libft.h"
# include "../minilibx/include/MLX42/MLX42.h"
# include <fcntl.h>

// Configuration constants
# define TILE_SIZE 32
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

// Map elements
# define WALL '1'
# define EMPTY '0'
# define COLLECTIBLE 'C'
# define PLAYER 'P'
# define EXIT 'E'

// Error messages
# define ERR_MAP_EXT "Error\nInvalid map extension (must be .ber)\n"
# define ERR_MAP_EMPTY "Error\nEmpty map\n"
# define ERR_MAP_RECT "Error\nMap must be rectangular\n"
# define ERR_MAP_WALLS "Error\nMap must be surrounded by walls\n"
# define ERR_MAP_CHARS "Error\nInvalid character in map\n"
# define ERR_MAP_MISSING "Error\nMissing elements in map\n"
# define ERR_INIT_MLX "Error\nFailed to initialize MLX\n"
# define ERR_LOAD_TEXTURES "Error\nFailed to load textures\n"
# define ERR_PARSE_MAP "Error\nFailed to parse map\n"

// Structures
typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		collectibles;
	int		exit;
	int		player;
}			t_map;

typedef struct s_game
{
	mlx_t		*mlx;
	t_map		*map;
	mlx_image_t	*player;
	mlx_image_t	*wall;
	mlx_image_t	*collectible;
	mlx_image_t	*exit;
	mlx_image_t	*floor;
	int			collected;
	int			moves;
	int			player_x;
	int			player_y;
}				t_game;

// Initialization functions
int			init_game(t_game *game, char *map_path);
int			init_textures(t_game *game);

// Map handling functions
int			check_map_extension(char *filename);
int			parse_map(t_game *game, char *map_path);
void		free_map(t_map *map);
int			validate_map(t_map *map);
int			check_map_elements(t_map *map);
int			check_map_walls(t_map *map);

// Game mechanics functions
void		move_player(t_game *game, int dx, int dy);
void		handle_input(mlx_key_data_t keydata, void *param);
void		render_map(t_game *game);
void		cleanup_game(t_game *game);

#endif
