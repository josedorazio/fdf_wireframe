/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:48:39 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/08 13:37:14 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

int	map_init(char *file, t_map *map)
{
	map->height = 0;
	map->width = 0;
	map->color = 0;
	map->z_max = INT_MIN;
	map->z_min = INT_MAX;
	if (get_height(file, map))
		return (1);
	printf("Map Height %d\n", map->height);
	if (get_width(file, map))
		return (1);
	printf("Map Width %d\n", map->width);
	return (0);
}

void	z_values(t_map *map)
{
	int	y;
	int	x;
 	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->matrix[y][x] < map->z_min)
				map->z_min = map->matrix[y][x];
			else if (map->matrix[y][x] > map->z_max)
				map->z_max = map->matrix[y][x];
			x++;
		}
		y++;
	}
}

int	fill_matrix(int fd, t_map *map)
{
	char	*line;
	char	**arr;
	int		i;
	int		j;

	i = 0;
	while (i < map->height)
	{
		line = get_next_line(fd);
		if (!line)
			return (1);
		arr = ft_split(line, ' ');
		free(line);
		if (!arr)
			return (1);
		j = 0;
		map->matrix[i] = malloc(map->width * sizeof(int));
		while (j < map->width && arr[j] != NULL)
		{
			map->matrix[i][j] = convert(arr[j]);
			j++;
		}
		free_array(arr);
		i++;
	}
	return (0);
}


void	load_map(char *file, t_map *map)
{
	int		fd;

	// ## FALTA AGREGAR UN CONTROL DE SI EL ARCHIVO ES .FDF

	if (map_init(file, map))
	terminate(31, NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	terminate(2, NULL);
	map->matrix = malloc(map->height * sizeof(int *));
	if (!map->matrix)
		exit(EXIT_FAILURE);
	if (fill_matrix(fd, map) == 1)
	{
		printf("failed to create matrix\n");
		exit(EXIT_FAILURE);
	}
	z_values(map);	
}
