/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:50:21 by jdorazio          #+#    #+#             */
/*   Updated: 2025/02/14 09:19:56 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	init_display_mlx(t_map *map, t_display *mlx)
{
	mlx->map = *map;
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (1);
	mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img.img)
		return (1);
	printf("img.img works\n");
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "FDF - Wireframe");
	if (!mlx->win)
		return (1);
	printf("img.win works\n");
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel,
			&mlx->img.line_length, &mlx->img.endian);
	if (!mlx->img.addr)
		return (1);
	printf("img.addr works\n");
	return (0);
}

int	system_init(t_map *map)
{
	t_display	*mlx;

	ft_printf("Initializing Minilibx...\n");
	mlx = ft_calloc(1, sizeof(t_display));
	if (!mlx)
		terminate(6, mlx);
	mlx->zoom = 1;
	if (init_display_mlx(map, mlx))
		terminate(6, mlx);
	mlx_hook(mlx->win, KP, (1L<<0), key_hook, mlx);
	mlx_hook(mlx->win, DN, (1L<<17), free_close, mlx);
	draw_map(mlx);
	mlx_loop(mlx->mlx);
	return (EXIT_SUCCESS);
}
