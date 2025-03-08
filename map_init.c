/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:48:39 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/08 16:24:40 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	map_init(char *file, t_map *map)
{
	map->height = 0;
	map->width = 0;
	map->color = 0;
	map->z_max = INT_MIN;
	map->z_min = INT_MAX;
	if (get_height(file, map))
		return (1);
	if (get_width(file, map))
		return (1);
	map->matrix = malloc(map->height * sizeof(int *));
	map->color = malloc(map->height * sizeof(int *));
	if (!map->matrix || !map->color)
		return (1);
	return (0);
}

int	init_matrix(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		map->matrix[i] = malloc(map->width * sizeof(int));
		map->color[i] = malloc(map->width * sizeof(int));
		if (!map->matrix[i] || !map->color[i])
		{
			while (i >= 0) // Free previous allocations before returning
			{
				free(map->matrix[i]);
				free(map->color[i]);
				i--;
			}
			free(map->matrix);
			free(map->color);
			return (1);
		}
		i++;
	}
	return (0);
}

int	fill_matrix(int fd, t_map *map)
{
	char	*line;
	char	**arr;
	int		i;
	int		j;

	i = -1;
	while (++i < map->height)
	{
		line = get_next_line(fd);
		if (!line)
			return (1);
		arr = ft_split(line, ' ');
		free(line);
		if (!arr)
			return (1);
		j = -1;
		while (++j < map->width)
			convert(arr[j], &map->matrix[i][j], &map->color[i][j]);
		free_array(arr);
	}
	return (0);
}



void	load_map(char *file, t_map *map)
{
	int		fd;

	if (check_extension(file))
		terminate(1, NULL);
	if (map_init(file, map))
		terminate(31, NULL);
	if (init_matrix(map))
		terminate(33, NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		terminate(2, NULL);
	if (fill_matrix(fd, map) == 1)
	{
		printf("Failed to create matrix\n");
		// Free all allocated memory before exiting
		for (int i = 0; i < map->height; i++)
		{
			free(map->matrix[i]);
			free(map->color[i]);
		}
		close(fd);
		free(map->matrix);
		free(map->color);
		exit(EXIT_FAILURE);
	}
	close(fd);
	z_values(map);
}
