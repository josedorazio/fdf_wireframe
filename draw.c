/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:56:28 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/11 20:13:07 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_map(t_display *mlx)
{
	int	x;
	int	y;

	ft_bzero(mlx->img->addr, WIDTH * HEIGHT * (mlx->img->bits_per_pixel / 8));
	draw_sidebar(mlx);
	y = 0;
	while (y < mlx->map->height)
	{
		x = 0;
		while (x < mlx->map->width)
		{
			if (x < mlx->map->width - 1)
				bresenham_line(mlx, create_point(x, y, mlx),
					create_point(x + 1, y, mlx));
			if (y < mlx->map->height - 1)
				bresenham_line(mlx, create_point(x, y, mlx),
					create_point(x, y + 1, mlx));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img, 0, 0);
	sidebar_description(mlx);
}

void	init_bresenham_line(t_point *p1, t_point *p2, t_delta *delta)
{
	int	x_sign;
	int	y_sign;

	delta->dx = abs(p2->sx - p1->sx);
	delta->dy = abs(p2->sy - p1->sy);
	x_sign = -1;
	y_sign = -1;
	if (p2->sx > p1->sx)
		x_sign = 1;
	if (p2->sy > p1->sy)
		y_sign = 1;
	delta->sign_x = x_sign;
	delta->sign_y = y_sign;
}

void	bresenham_step(t_point *p1, t_delta *delta, int *err)
{
	int	err2;

	err2 = 2 * (*err);
	if (err2 > -delta->dy)
	{
		*err -= delta->dy;
		p1->sx += delta->sign_x;
	}
	if (err2 < delta->dx)
	{
		*err += delta->dx;
		p1->sy += delta->sign_y;
	}
}

void	bresenham_line(t_display *mlx, t_point p1, t_point p2)
{
	t_delta	delta;
	int		err;
	int		steps;
	float	t;
	int		color;

	t = 0.0;
	if ((abs(p2.sx - p1.sx) > abs(p2.sy - p1.sy)))
		steps = abs(p2.sx - p1.sx);
	else
		steps = abs(p2.sy - p1.sy);
	init_bresenham_line(&p1, &p2, &delta);
	err = delta.dx - delta.dy;
	while (p1.sx != p2.sx || p1.sy != p2.sy)
	{
		color = interpolate_color(p1.color, p2.color, t / steps);
		put_pixel(mlx, p1.sx, p1.sy, color);
		t++;
		bresenham_step(&p1, &delta, &err);
	}
}

void	put_pixel(t_display *mlx, int x, int y, int color)
{
	int	pixel;

	if (x >= WIDTH || x < 0 || y < 0 || y >= HEIGHT)
		return ;
	pixel = (y * mlx->img->line_length) + (x * (mlx->img->bits_per_pixel / 8));
	*(unsigned int *)(mlx->img->addr + pixel) = color;
}
