/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:48:39 by jdorazio          #+#    #+#             */
/*   Updated: 2025/02/12 18:57:23 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

void	map_dimensions(char *file, t_map *map)
{
	int		fd;

	vertical_dim(file, map);
	map->width = malloc(map->height * sizeof(int));
	if (!map->width)
		terminate(4, map);
	fd = open(file, O_RDONLY);
	if (fd < 0)
			terminate(3, file);
	horizontal_dim(fd, map);
	close (fd);
}


void	map_init(char *file, t_map *map)
{
	int		i;
	int		fd;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
		terminate(3, file);
	map_dimensions(file, map);
	close (fd);
	map->matrix = (int **)ft_calloc(map->height, sizeof(int *));
	if (!map->matrix)
		terminate(4, map);
	i = 0;
	while (i < map->height)
	{
		map->matrix[i] = ft_calloc(map->width[i], sizeof(int));
		if (!map->matrix[i])
			terminate(4, map);
		i++;
	}
}

void	fill_matrix(int fd, t_map *map)
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
			break;
		arr = ft_split(line, ' ');
		free(line);
		j = 0;
		while (j < map->width[i] && arr[j] != NULL)
		{
			map->matrix[i][j] = convert(arr[j]);
			free(arr[j]);
			j++;
		}
		free(arr);
		i++;
	}
}

void	load_map(char *file, t_map *map)
{
	int		fd;

	// ## FALTA AGREGAR UN CONTROL DE SI EL ARCHIVO ES .FDF

	// ------------------------- //
	map_init(file, map);
	// USE TERMINATE FUNCTION FOR ERROR HANDLING
	fd = open(file, O_RDONLY);
	if (fd < 0)
		terminate(3, file);
	fill_matrix(fd, map);
	close(fd);
	map->z_min = INT_MAX;
	map->z_max = INT_MIN;
	z_values(map);
}

void	z_values(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width[y])
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
