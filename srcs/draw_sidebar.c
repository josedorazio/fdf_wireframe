/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sidebar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:35:59 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/11 19:45:20 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_sidebar(t_display *mlx)
{
	int	x;
	int	y;

	if (!mlx)
		terminate(5);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < SIDEBAR)
		{
			put_pixel(mlx, x, y, 0x202020);
			x++;
		}
		y++;
	}
}

void	sidebar_description(t_display *mlx)
{
	int	vp;

	vp = 100;
	mlx_string_put(mlx->mlx, mlx->win, 25, vp, 0xFFFFFF, "Welcome");
	mlx_string_put(mlx->mlx, mlx->win, 25, vp += 75, 0xFFFFFF, "Controls");
	mlx_string_put(mlx->mlx, mlx->win, 25, vp += 25,
		0xFFFFFF, "Zoom In/Out: Scroll or '+' / '-'");
	mlx_string_put(mlx->mlx, mlx->win, 25, vp += 25, 0xFFFFFF,
		"Rotate X-Axis: '1' / '2'");
	mlx_string_put(mlx->mlx, mlx->win, 25, vp += 25, 0xFFFFFF,
		"Rotate Y-Axis: '3' / '4'");
	mlx_string_put(mlx->mlx, mlx->win, 25, vp += 25, 0xFFFFFF,
		"Rotate Z-Axis: '5' / '6'");
	mlx_string_put(mlx->mlx, mlx->win, 25, vp += 25, 0xFFFFFF,
		"Exit: Press 'ESC' or Click in 'x'");
}
