/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:48:39 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/12 15:34:36 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	map_init(char *file, t_map *map)
{
	map->height = 0;
	map->width = 0;
	map->z_max = INT_MIN;
	map->z_min = INT_MAX;
	if (get_height(file, map))
		terminate (3);
	if (get_width(file, map))
		terminate (3);
	map->matrix = ft_calloc(map->height, sizeof(int *));
	map->color = ft_calloc(map->height, sizeof(int *));
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
		map->matrix[i] = ft_calloc(map->width, sizeof(int));
		map->color[i] = ft_calloc(map->width, sizeof(int));
		if (!map->matrix[i] || !map->color[i])
			terminate(1);
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
		terminate(1);
	if (map_init(file, map))
		terminate(2);
	if (init_matrix(map))
		terminate(3);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		terminate(2);
	if (fill_matrix(fd, map) == 1)
		terminate(3);
	ft_printf("Starting to load Map\n");
	close(fd);
	z_values(map);
	ft_printf("Map loaded!\n");
}
