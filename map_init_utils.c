/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:05:50 by jdorazio          #+#    #+#             */
/*   Updated: 2025/02/26 18:46:47 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

int	vertical_dim(char *file, t_map *map)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
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

char *trim_newline(int fd)
{
	char	*line;
	int		len;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
		line[--len] = '\0';
	return (line);
}

int	horizontal_dim(int fd, t_map *map)
{
	char	*line;
	char	**arr;
	int		cols;
	int		i;

	i = 0;
	while (i < map->height)
	{
		cols = 0;
		line = trim_newline(fd);
		if (!line)
			return (1);
		arr = ft_split(line, ' ');
		free(line);
		if (!arr)
			return (1);
		while (arr[cols] && (arr[cols][0] != '\0' || arr[cols][0] != '\r'))
			cols++;
		map->width[i] = cols;
		free_array(arr);
		i++;
	}
	return (0);
}
