/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:05:50 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/08 16:20:13 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

int	get_height(char *file, t_map *map)
{
	int		fd;
	char	*line;

	if ((fd = open(file, O_RDONLY) )< 0)
		return (1);
	map->height = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		map->height++;
		free(line);
	}
	close(fd);
	return (0);
}

int	data_counter(char *line)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i]) {
		// Saltar espacios iniciales
		while (line[i] && line[i] == ' ')
			i++;
		// Contar palabras
		if (line[i] && line[i] != ' ') {
			count++;
			// Saltar caracteres de la palabra actual
			while (line[i] && line[i] != ' ')
				i++;
		}
	}
	return count;
}

int	get_width(char *file, t_map *map)
{
	char	*line;
	int		curr;
	int		prev;
	int		fd;

	prev = 0;
	if ((fd = open(file, O_RDONLY)) < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		curr = data_counter(line);
		if (prev != 0 && curr != prev)
		{
			free(line);
			close(fd);
			return (1);
		}
		map->width = curr;
		prev = curr;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
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

int	check_extension(char *file)
{
	char	*extension;

	extension = ft_strrchr(file, '.');
	if (!extension)
		return (1);
	if (extension && ft_strncmp(extension, ".fdf", 5) == 0)
		return (0);
	return (1);
}
