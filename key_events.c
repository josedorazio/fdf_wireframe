/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 22:57:25 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/11 19:41:58 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_display *mlx)
{
	if (keycode == KEY_ESC)
		free_close(mlx);
	if (keycode == KEY_SUM || keycode == KEY_SUM2)
		mlx->zoom *= 1.1;
	else if (keycode == KEY_MINUS || keycode == KEY_MINUS2)
		mlx->zoom /= 1.1;
	if (keycode == KEY_1 || keycode == KEY_2
		|| keycode == KEY_3 || keycode == KEY_4
		|| keycode == KEY_5 || keycode == KEY_6)
		update_rot(keycode, mlx);
	if (mlx->img && mlx->img->img)
		mlx_destroy_image(mlx->mlx, mlx->img->img);
	mlx->img->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->img->addr = mlx_get_data_addr(mlx->img->img, &mlx->img->bits_per_pixel,
			&mlx->img->line_length, &mlx->img->endian);
	draw_map(mlx);
	return (0);
}

void	update_rot(int keycode, t_display *mlx)
{
	if (keycode == KEY_1)
		mlx->rot_x -= (2 * M_PI / 180);
	else if (keycode == KEY_2)
		mlx->rot_x += (2 * M_PI / 180);
	else if (keycode == KEY_3)
		mlx->rot_y -= (2 * M_PI / 180);
	else if (keycode == KEY_4)
		mlx->rot_y += (2 * M_PI / 180);
	else if (keycode == KEY_5)
		mlx->rot_z -= (2 * M_PI / 180);
	else if (keycode == KEY_6)
		mlx->rot_z += (2 * M_PI / 180);
}
