/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:05:50 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/08 12:56:58 by jdorazio         ###   ########.fr       */
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
