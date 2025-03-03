/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:50:21 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/03 21:36:20 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	init_display_mlx(t_display *mlx)
{
	mlx->mlx = mlx_init();
	mlx->img = (t_image *)ft_calloc(1, sizeof(t_image));  // or a similar initialization

	mlx->img->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->img->addr = mlx_get_data_addr(mlx->img->img, &mlx->img->bits_per_pixel,
			&mlx->img->line_length, &mlx->img->endian);
	printf("MLX->WIN START\n");
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "FDF - Wireframe");
	printf("MLX->XIN NO ERROR \n");
	return (0);
}

int	set_display_default(t_display *mlx, t_map *map)
{

	mlx->map = map;
	mlx->zoom = 1.0;
	mlx->rot_x = 0.0;
	mlx->rot_y = 0.0;
	mlx->rot_z = 0.0;
	mlx->angle = 45.0; //cambiar
	return (0);
}

void	system_init(t_map *map)
{
	t_display	*mlx;

	ft_printf("Initializing Minilibx...\n");
	mlx = (t_display *)ft_calloc(1, sizeof(t_display));
	if (!mlx)
	{
		printf("MLX failed in system init\n\n");
		exit(EXIT_FAILURE);
	}
	if (set_display_default(mlx, map) == 1)
	{
		free_mlx_map(mlx);
		free_map(map);
		printf("ERROR SETTING\n");
		exit(EXIT_FAILURE);
	}
	printf("Starting Init Display MLX\n");
	if (init_display_mlx(mlx) == 1)
	{
		free_mlx_map(mlx);
		free_map(map);
		printf("INIT DISPLAY_MLX(MLX) freeing correctly\n");
		exit(EXIT_FAILURE);
	}
	mlx_hook(mlx->win, KP, (1L<<0), key_hook, mlx);
	mlx_hook(mlx->win, DN, (1L<<17), free_close, mlx);
	draw_map(mlx);
	mlx_loop(mlx->mlx);
	free_mlx_map(mlx);
	free(mlx);
}
