/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 22:57:25 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/10 20:24:23 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_display *mlx)
{
	if (keycode == KEY_ESC)
		free_close(mlx);
	/*ZOOM IN ||ZOOM OUT*/
	if (keycode == KEY_SUM || keycode == KEY_SUM2)
		mlx->zoom *= 1.1;
	else if (keycode == KEY_MINUS || keycode == KEY_MINUS2)
		mlx->zoom /= 1.1;
	if (keycode == KEY_1 || keycode == KEY_2
		|| keycode == KEY_3 || keycode == KEY_4)
		update_rot(keycode, mlx);
	/* --------------------- */
	/* Borrar imagen anterior y redibujar */
	if (mlx->img->img)
		mlx_destroy_image(mlx->mlx, mlx->img->img);  // Destruye la imagen anterior
	mlx->img->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->img->addr = mlx_get_data_addr(mlx->img->img, &mlx->img->bits_per_pixel,
		&mlx->img->line_length, &mlx->img->endian);
	draw_map(mlx);
	return (0);
}

int	mouse_hook(int button, t_display *mlx)
{
	if (button == 4)
		mlx->zoom += 2;
	else if (button == 5 && mlx->zoom > 2)
		mlx->zoom -= 2;
	return (0);
}

void	update_rot(int keycode, t_display *mlx)
{
	if (keycode == KEY_1)
		mlx->rot_x -= (2 * M_PI / 180);
	else if (keycode == KEY_2)
		mlx->rot_x += (2 * M_PI / 180);
	else if (keycode == KEY_3)
		mlx->rot_z -= (2 * M_PI / 180);
	else
		mlx->rot_z += (2 * M_PI / 180);
}

