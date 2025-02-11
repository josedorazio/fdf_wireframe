/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 23:25:46 by jdorazio          #+#    #+#             */
/*   Updated: 2025/02/11 23:38:53 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

int	free_close(t_display *mlx)
{
	free_display(mlx);
	ft_printf("FDF Closed Correctly\n");
	exit(EXIT_SUCCESS);
	return (0);
}

void	free_display(t_display *mlx)
{
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_image(mlx->mlx, mlx->img.img);
	if (mlx->map.matrix)
		free_map(&mlx->map);
	free(mlx);
}

void	free_map(t_map *map)
{
	int	y;

	y = 0;
	if (map->matrix)
	{
		while (y < map->height)
		{
			free(map->matrix[y]);
			y++;
		}
		free(map->matrix);
	}
	ft_printf("Map freed\n");
}
