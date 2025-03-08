/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:56:28 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/08 12:58:35 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"


void	draw_map(t_display *mlx)
{
	int	x;
	int	y;

	ft_bzero(mlx->img->addr, WIDTH * HEIGHT * (mlx->img->bits_per_pixel / 8));
	ft_printf("Drawing map...\n");
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
	ft_printf("Drawing Complete. Updating Window...\n");
	draw_sidebar(mlx);
	mlx_put_image_to_window(mlx->mlx,  mlx->win, mlx->img->img, 0 ,0);
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


void	bresenham_line(t_display *mlx, t_point p1, t_point p2)
{
	t_delta	delta;
	int		err;
	int		err2;

	init_bresenham_line(&p1, &p2, &delta);
	err = delta.dx - delta.dy;
	while (p1.sx != p2.sx || p1.sy != p2.sy)
	{
		put_pixel(mlx, p1.sx, p1.sy, 0xFFFFFF);
		err2 = 2 * err;
		if (err2 > -delta.dy)
		{
			err -= delta.dy;
			p1.sx += delta.sign_x;
		}
		if (err2 < delta.dx)
		{
			err += delta.dx;
			p1.sy += delta.sign_y;
		}
	}
}

void	put_pixel(t_display *mlx, int x, int y, int color)
{
	int	pixel;

	if (x >= WIDTH || x < 0 || y <0 || y >= HEIGHT)
		return ;
	pixel = (y * mlx->img->line_length) + (x * (mlx->img->bits_per_pixel / 8));
	*(unsigned int *)(mlx->img->addr + pixel) = color;	
}


t_point	create_point(int x, int y, t_display *mlx)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = mlx->map->matrix[y][x];
	isometric(&point, mlx);
	return (point);

}

void	isometric(t_point *p, t_display *mlx)
{
	int x_offset;
	int y_offset;
	
	x_offset = WIDTH / 2;
	y_offset= HEIGHT / 2;
	p->x = p->x * mlx->zoom * ZOOM;
	p->y = p->y * mlx->zoom* ZOOM;
	p->z = (p->z  * mlx->zoom * ZOOM) / 4;
	rot_x(p, mlx->rot_x);
	rot_z(p, mlx->rot_z);
	p->sx = ((p->x - p->y) * cos(-M_PI / 6)) + x_offset;
	p->sy = ((p->x + p->y) * sin (-M_PI / 6) - p->z) + y_offset;
}
void	rot_x(t_point *p, float angle)
{
	int	y;
	int	z;

	y = p->y * cos(angle) - p->z * sin(angle);
	z = p->y * sin(angle) + p->z * cos(angle);
	p->y = y;
	p->z = z;
}

void	rot_z(t_point *p, float angle)
{
	int	x;
	int	y;

	y = p->x * cos(angle) - p->y * sin(angle);
	x = p->x * sin(angle) + p->y * cos(angle);
	p->y = y;
	p->x = x;
}
