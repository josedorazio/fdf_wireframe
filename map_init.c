/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:48:39 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/03 21:31:58 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

void	map_init(char *file, t_map *map)
{
	int		i;

	if (map_dimensions(file, map) == 1)
	{
		free(map->width);
		exit(EXIT_FAILURE);
	}
	map->matrix = malloc(map->height * sizeof(int *));
	if (!map->matrix)
	{
		free(map->width);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < map->height)
	{
		map->matrix[i] = ft_calloc(map->width[i], sizeof(int));
		if (!map->matrix[i])
		{
			while (i > 0)
				free(map->matrix[--i]);
			free(map->matrix);
			free(map->width);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

int	map_dimensions(char *file, t_map *map)
{
	int	fd;


	if (vertical_dim(file, map) == 1)
		return (1);
	if (map->height <= 0)
		return (1);
	map->width = malloc(map->height * sizeof(int));
	if (!map->width)
		return (1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		free(map->width);
		return (1);
	}
	if(horizontal_dim(fd, map) == 1)
	{
		free(map->width);
		close (fd);
		return (1);
	}
	close (fd);
	return (0);
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
		while (j < map->width[i] && arr[j] != NULL)
		{
			map->matrix[i][j] = convert(arr[j]);
			j++;
		}
		free_array(arr);
		i++;
	}
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

void	load_map(char *file, t_map *map)
{
	int		fd;

	// ## FALTA AGREGAR UN CONTROL DE SI EL ARCHIVO ES .FDF

	// ------------------------- //
	map = NULL;
	map_init(file, map);
	// USE TERMINATE FUNCTION FOR ERROR HANDLING
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	if (fill_matrix(fd, map) == 1)
	{
		free(map->width);
		exit(EXIT_FAILURE);
	}
	close(fd);
	map->z_min = INT_MAX;
	map->z_max = INT_MIN;
	z_values(map);
}
