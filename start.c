/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:50:21 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/11 19:58:20 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	init_display_mlx(t_display *mlx)
{
	if (!mlx)
		return (1);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "FDF - Wireframe");
	mlx->img = ft_calloc(1, sizeof(t_image));
	if (!mlx->img)
		return (1);
	mlx->img->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->img->addr = mlx_get_data_addr(mlx->img->img, &mlx->img->bits_per_pixel,
			&mlx->img->line_length, &mlx->img->endian);
	if (!mlx->mlx || !mlx->img->img || !mlx->img->addr
		|| !mlx->win)
		return (1);
	return (0);
}

int	set_display_default(t_display *mlx, t_map *map)
{
	int	max_size;

	mlx->map = map;
	mlx->map = map;
	max_size = map->height;
	if (map->width > map->height)
		max_size = map->width;
	mlx->zoom = (WIDTH / max_size) * 0.4;
	mlx->rot_x = 0;
	mlx->rot_y = 0;
	mlx->rot_z = 0;
	return (0);
}

void	system_init(t_map *map)
{
	t_display	*mlx;

	mlx = ft_calloc(1, sizeof(t_display));
	if (!mlx)
		terminate(4);
	if (set_display_default(mlx, map) == 1)
	{
		free_mlx_map(mlx);
		free_map(map);
		terminate(5);
	}
	ft_printf("Starting Init Display MLX\n");
	if (init_display_mlx(mlx) == 1)
	{
		free_mlx_map(mlx);
		free_map(map);
		terminate(5);
	}
	mlx_hook(mlx->win, KP, (1L << 0), key_hook, mlx);
	mlx_hook(mlx->win, DN, (1L << 17), free_close, mlx);
	ft_printf("Drawing map...\n");
	draw_map(mlx);
	mlx_loop(mlx->mlx);
	free_mlx_map(mlx);
	free(mlx);
}
