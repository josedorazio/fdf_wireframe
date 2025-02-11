/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:50:21 by jdorazio          #+#    #+#             */
/*   Updated: 2025/02/10 22:47:34 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"


int	init_display_mlx(t_map *map, t_display *mlx)
{
	mlx->map = map;
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (1);
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "FDF");
	if (!mlx->mlx)
		return (1);
	mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img.img)
		return (1);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel, &mlx->img.line_length,
		&mlx->img.endian);
	if (mlx->img.addr)
		return (1);
	return (0);
}

void	system_init(t_map *map)
{
	t_display	*mlx;

	ft_printf("Initializing Minilibx...\n");
	mlx = ft_calloc(1, sizeof(t_display));
	if (!mlx)
		terminate(5);
	if (!init_display_mlx(map, mlx))
		terminate(5);
	draw_map(map);
	mlx_loop(mlx->mlx);
}


void	draw_map(t_map *map)
{
	isometric_proj(map);

}


/*
1. Guardamos Los Puntos
2. Aplicamos


*/





void	isometric_proj(t_map *map)
{
}

t_point create_point()
{

}

void	init_Bresenham_line (int x1, int y1, int x2, int y2)
{
	int	dY;
	int	dX;

	dY = y2 - y1;
	dX = x2 - x1;
	if (dY >= 0)
		dY;
	sign_x = -1;
	if (dX >= 0)
	
	

}
