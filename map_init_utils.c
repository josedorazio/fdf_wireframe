/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:05:50 by jdorazio          #+#    #+#             */
/*   Updated: 2025/02/12 19:36:18 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

void	vertical_dim(char *file, t_map *map)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		terminate(3, file);
	map->height = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		map->height++;
		free(line);
	}
}

void	horizontal_dim(int fd, t_map *map)
{
	char	*line;
	char	**arr;
	int		cols;
	int		i;

	i = 0;
	while (i < map->height)
	{
		cols = 0;
		line = clear_line(fd);
		arr = ft_split(line, ' ');
		if (!arr)
			free(arr);
		while (arr[cols])
		{
			if (arr[cols][0] != '\0' || arr[cols][0] != '\r')
				cols++;
			free(arr[cols]);
		}
		free(arr);
		map->width[i] = cols;
		free(line);
		i++;
	}

}

char *clear_line(int fd)
{
	char	*line;
	int		len;

	line = get_next_line(fd);
	if (!line)
		terminate(3, line);
	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
		line[--len] = '\0';
	return (line);
}
