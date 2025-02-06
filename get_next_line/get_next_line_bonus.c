/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:48:34 by jdorazio          #+#    #+#             */
/*   Updated: 2024/10/24 12:42:08 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_update_string(char *left_string)
{
	char	*update_string;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!left_string)
		return (NULL);
	while (left_string[i] && left_string[i] != '\n')
		i++;
	if (left_string[i] == '\n')
		i++;
	if (left_string[i] == '\0')
		return (NULL);
	update_string = malloc((ft_strlen(left_string) - i + 1) * sizeof(char));
	if (!update_string)
		return (NULL);
	while (left_string[i])
		update_string[j++] = left_string[i++];
	update_string[j] = '\0';
	return (update_string);
}

char	*ft_extract_line(char *left_string)
{
	int		i;
	int		j;
	char	*extract_line;

	i = 0;
	j = 0;
	if (!left_string || *left_string == '\0')
		return (NULL);
	while (left_string[i] && left_string[i] != '\n')
		i++;
	if (left_string[i] == '\n')
		i++;
	extract_line = malloc((i + 1) * sizeof(char));
	if (!extract_line)
		return (NULL);
	while (j < i)
	{
		extract_line[j] = left_string[j];
		j++;
	}
	extract_line[j] = '\0';
	return (extract_line);
}

char	*ft_free(char *left_string, char *buffer)
{
	char	*temp;

	if (!left_string)
		left_string = ft_strdup("");
	temp = ft_strjoin(left_string, buffer);
	free(left_string);
	return (temp);
}

char	*ft_read_to_buffer(int fd, char *left_string)
{
	int		b_read;
	char	*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read == -1)
			return (free(buffer), free(left_string), NULL);
		if (b_read == 0)
			break ;
		buffer[b_read] = '\0';
		left_string = ft_free(left_string, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (free(buffer), left_string);
}

char	*get_next_line(int fd)
{
	static char	*left_string[OPEN_MAX];
	char		*extract_line;
	char		*update_string;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (NULL);
	left_string[fd] = ft_read_to_buffer(fd, left_string[fd]);
	if (!left_string[fd])
		return (NULL);
	extract_line = ft_extract_line(left_string[fd]);
	if (!extract_line)
	{
		free(left_string[fd]);
		left_string[fd] = NULL;
		return (NULL);
	}
	update_string = ft_update_string(left_string[fd]);
	free(left_string[fd]);
	left_string[fd] = update_string;
	return (extract_line);
}
