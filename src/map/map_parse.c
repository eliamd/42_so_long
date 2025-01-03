/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:09:12 by edetoh            #+#    #+#             */
/*   Updated: 2025/01/03 13:24:08 by edetoh           ###   ########.fr       */
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
		return (close(fd), 0);
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
	return (close(fd), 1);
}

static void	free_grid_until(t_map *map, int y)
{
	while (y >= 0)
	{
		if (map->grid[y])
		{
			free(map->grid[y]);
			map->grid[y] = NULL;
		}
		y--;
	}
	free(map->grid);
	map->grid = NULL;
}

static int	allocate_and_copy_line(t_map *map, int y, char *line)
{
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	map->grid[y] = (char *)malloc(sizeof(char) * (map->width + 1));
	if (!map->grid[y])
	{
		free(line);
		free_grid_until(map, y - 1);
		return (0);
	}
	ft_strlcpy(map->grid[y], line, map->width + 1);
	return (1);
}

static int	read_map_line(int fd, t_map *map, int y)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (0);
	if (!allocate_and_copy_line(map, y, line))
		return (0);
	free(line);
	if ((int)ft_strlen(map->grid[y]) != map->width)
	{
		free_grid_until(map, y);
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
		{
			write(1, "ici2\n", 5);
			return (0);
		}
	}
	close(fd);
	return (1);
}
