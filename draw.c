/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:56:28 by jdorazio          #+#    #+#             */
/*   Updated: 2025/02/12 23:23:26 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"


void	draw_map(t_display *mlx)
{
	int	x;
	int	y;

	ft_printf("Drawing map...\n");
	y = 0;
	while (y < mlx->map.height)
	{
		x = 0;
		while (x < mlx->map.width[y])
		{
			if (x < mlx->map.width[y] - 1)
				bresenham_line(mlx, create_point(x, y, mlx),
					create_point(x + 1, y, mlx));
			if (y < mlx->map.height - 1)
				bresenham_line(mlx, create_point(x, y, mlx),
					create_point(x, y + 1, mlx));
			x++;
		}
		y++;
	}
	ft_printf("Drawing Complete. Updating Window...\n");
	mlx_put_image_to_window(mlx->mlx,  mlx->win, mlx->img.img, 0 ,0);
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
		printf("Entramos a bucle\n");
		put_pixel(&mlx->img, p1.sx, p1.sy, 0xFFFFFF);
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

void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) // Prevent segmentation faults
	{
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}


t_point	create_point(int x, int y, t_display *mlx)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = mlx->map.matrix[y][x];
	isometric(&point, mlx);
	return (point);

}

void	isometric(t_point *p, t_display *mlx)
{
	int		x;
	int		y;
	int		z;
	int x_offset = WIDTH / 2;
	int y_offset = HEIGHT / 2;
	//float	scale;

	//scale = fmin(WIDTH / mlx->map.width[0], HEIGHT / mlx->map.height / 2);
	x = p->x * mlx->zoom * ZOOM;
	y = p->y * mlx->zoom* ZOOM;
	z = (p->z  * mlx->zoom * ZOOM) / 4;
	p->sx = ((x - y) * cos(45)) + x_offset;
	p->sy = ((x + y) * sin (45) - z) + y_offset;
}
