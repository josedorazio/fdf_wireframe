/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:24:17 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/11 20:19:08 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rot_x(t_point *p, float angle)
{
	int	y;
	int	z;

	angle += -0.3;
	y = p->y * cos(angle) - p->z * sin(angle);
	z = p->y * sin(angle) + p->z * cos(angle);
	p->y = y;
	p->z = z;
}

void	rot_z(t_point *p, float angle)
{
	int	x;
	int	y;

	angle += M_PI;
	y = p->x * cos(angle) - p->y * sin(angle);
	x = p->x * sin(angle) + p->y * cos(angle);
	p->y = y;
	p->x = x;
}

void	rot_y(t_point *p, float angle)
{
	int	x;
	int	z;

	angle += 0;
	x = p->x * cos(angle) - p->z * sin(angle);
	z = p->x * sin(angle) + p->z * cos(angle);
	p->x = x;
	p->z = z;
}

void	isometric(t_point *p, t_display *mlx)
{
	int	x_offset;
	int	y_offset;

	x_offset = WIDTH - ((mlx->map->width * mlx-> zoom));
	y_offset = HEIGHT / 2 - ((mlx->map->height * mlx->zoom) / 2);
	p->x = p->x * mlx->zoom;
	p->y = p->y * mlx->zoom;
	p->z = (p->z * mlx->zoom) / 5;
	rot_x(p, mlx->rot_x);
	rot_y(p, mlx->rot_y);
	rot_z(p, mlx->rot_z);
	p->sx = ((p->x - p->y) * cos(-ANGLE)) + x_offset;
	p->sy = ((p->x + p->y) * sin (-ANGLE) - p->z) + y_offset;
}

t_point	create_point(int x, int y, t_display *mlx)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = mlx->map->matrix[y][x];
	if (mlx->map->color && mlx->map->color[0][0] == 0xFFFFFF)
		point.color = get_color(point.z, mlx);
	else
		point.color = mlx->map->color[y][x];
	isometric(&point, mlx);
	return (point);
}
