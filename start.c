/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:50:21 by jdorazio          #+#    #+#             */
/*   Updated: 2025/02/11 23:49:18 by jdorazio         ###   ########.fr       */
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
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "FDF");
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

void	system_init(t_map *map)
{
	t_display	*mlx;

	ft_printf("Initializing Minilibx...\n");
	mlx = ft_calloc(1, sizeof(t_display));
	if (!mlx)
		terminate(5);
	if (init_display_mlx(map, mlx))
		terminate(5);
	mlx_hook(mlx->win, KP, (1L<<0), key_hook, mlx);
	mlx_hook(mlx->win, DN, (1L<<17), free_close, mlx);
	draw_map(mlx);
	mlx_loop(mlx->mlx);
}

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

void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) // Prevent segmentation faults
	{
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void	bresenham_line(t_display *mlx, t_point p1, t_point p2)
{
	t_delta	delta;
	int		err;
	int		err2;

	init_bresenham_line(&p1, &p2, &delta);
	err = delta.dx - delta.dy;
	while (p1.x != p2.x || p1.y != p2.y)
	{
		put_pixel(&mlx->img, p1.x, p1.y, 0xFFFFFF);
		err2 = 2 * err;
		if (err2 > -delta.dy)
		{
			err -= delta.dy;
			p1.x += delta.sign_x;
		}
		if (err2 < delta.dx)
		{
			err += delta.dx;
			p1.y += delta.sign_y;
		}
	}
}

t_point	create_point(int x, int y, t_display *mlx)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = mlx->map.matrix[y][x];
	//printf("Before isometric: x=%d, y=%d, z=%d\n", point.x, point.y, point.z);
	isometric(&point, mlx);
	//printf("After isometric: x=%d, y=%d\n", point.x, point.y);

	return (point);

}

void	isometric(t_point *p, t_display *mlx)
{
	int		x;
	int		y;
	int		z;
	float	scale;
	float	height_scale;


	x = p->x;
	y = p->y;
	z = p->z;
	height_scale = HEIGHT / (mlx->map.z_max - mlx->map.z_min + 1);
	scale = 0;
	if (mlx->map.z_max - mlx->map.z_min != 0)
		scale = (float) (z - mlx->map.z_min) / (mlx->map.z_max - mlx->map.z_min);
	z = scale * height_scale;
    float x_scale = WIDTH / (19 + 1);
    float y_scale = HEIGHT / (mlx->map.height + 1) ;
    float total_scale = fmin(x_scale, y_scale) / 5; // Keep aspect ratio
	
	//printf("x_scale %f | y_scale %f | total %f\n", x_scale, y_scale, total_scale);
	//printf("%f\n", y_scale);
    // Centering offsets
    int x_offset = WIDTH / 2;
    int y_offset = HEIGHT / 2;
	p->x = ((x - y) * cos(M_PI / 6)) * total_scale + x_offset;
	p->y = ((x + y) * sin(M_PI / 6) - (z * height_scale)) * total_scale + y_offset;
}


void	init_bresenham_line(t_point *p1, t_point *p2, t_delta *delta)
{
	int	x_sign;
	int	y_sign;

	x_sign = -1;
	y_sign = -1;
	delta->dx = abs(p2->x - p1->x);
	delta->dy = abs(p2->y - p1->y);
	if (p2->x > p1->x)
		x_sign = 1;
	if (p2->y > p1->y)
		y_sign = 1;
	delta->sign_x = x_sign;
	delta->sign_y = y_sign;
}

