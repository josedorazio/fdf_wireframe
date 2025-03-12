/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 23:25:46 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/11 20:41:52 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	free_close(t_display *mlx)
{
	free_mlx_map(mlx);
	ft_printf("FDF Closed Correctly\n");
	exit(EXIT_SUCCESS);
}

void	free_map(t_map *map)
{
	int	y;

	y = 0;
	while (y < map->height)
	{
		free(map->matrix[y]);
		if (map->color[y])
			free(map->color[y]);
		y++;
	}
	free(map->matrix);
	if (map->color)
		free(map->color);
	ft_printf("Map freed\n");
}

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_mlx_map(t_display *mlx)
{
	if (mlx->img->img)
		mlx_destroy_image(mlx->mlx, mlx->img->img);
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->mlx)
	{
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
	if (mlx->map->matrix)
		free_map(mlx->map);
	if (mlx->img)
		free(mlx->img);
	free(mlx);
	ft_printf("Freed Display\n");
}
