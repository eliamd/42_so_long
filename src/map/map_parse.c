/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:09:12 by edetoh            #+#    #+#             */
/*   Updated: 2024/12/27 22:07:18 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	get_map_size(char *map_path, t_map *map)
{
	int		fd;
	char	*line;
	size_t	len;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (0);
	map->height = 0;
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (0);
	}
	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		map->width = len - 1;
	else
		map->width = len;
	while (line)
	{
		free(line);
		map->height++;
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

static int	allocate_grid(t_map *map)
{
	map->grid = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		return (0);
	map->grid[map->height] = NULL;
	return (1);
}

static int	read_map_line(int fd, t_map *map, int y)
{
	char	*line;
	size_t	len;

	line = get_next_line(fd);
	if (!line)
		return (0);
	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		line[len - 1] = '\0';
	map->grid[y] = ft_strdup(line);
	free(line);
	if (!map->grid[y] || (int)ft_strlen(map->grid[y]) != map->width)
	{
		while (y >= 0)
			free(map->grid[y--]);
		free(map->grid);
		return (0);
	}
	return (1);
}

int	parse_map(t_game *game, char *map_path)
{
	int		fd;
	int		y;

	if (!get_map_size(map_path, game->map))
		return (0);
	if (!allocate_grid(game->map))
		return (0);
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (0);
	y = 0;
	while (y < game->map->height)
	{
		if (!read_map_line(fd, game->map, y++))
			return (0);
	}
	close(fd);
	return (1);
}
