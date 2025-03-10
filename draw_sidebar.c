/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sidebar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:35:59 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/10 20:24:46 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

void	draw_sidebar(t_display *mlx)
{
	int	x;
	int	y;

	ft_printf("Drawing Sidebar\n");
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
	mlx_string_put(mlx->mlx, mlx->win, 25, vp, 0xFFFFFF, "Draw Info");
	mlx_string_put(mlx->mlx, mlx->win, 25, vp+=75, 0xFFFFFF, "Map Info");
	mlx_string_put(mlx->mlx, mlx->win, 25, vp+=75, 0xFFFFFF, "Controls");
	mlx_string_put(mlx->mlx, mlx->win, 25, vp+=25, 0xFFFFFF, "Reset View:Press 'R'");
	mlx_string_put(mlx->mlx, mlx->win, 25, vp+=25, 0xFFFFFF, "Move View: Press 'A', 'W', 'S', 'D'");
	mlx_string_put(mlx->mlx, mlx->win, 25, vp+=25, 0xFFFFFF, "Zoom In/Out: Scroll or '+' / '-'");
	mlx_string_put(mlx->mlx, mlx->win, 25, vp+=25, 0xFFFFFF, "Rotate X-Axis: '1' / '2'");
	mlx_string_put(mlx->mlx, mlx->win, 25, vp+=25, 0xFFFFFF, "Rotate Y-Axis: '3' / '4'");
	mlx_string_put(mlx->mlx, mlx->win, 25, vp+=25, 0xFFFFFF, "Rotate Z-Axis: '5' / '6'");
	mlx_string_put(mlx->mlx, mlx->win, 25, vp+=25, 0xFFFFFF, "Exit: Press 'ESC' or Click in 'x'");
}

	// mlx_string_put(mlx->mlx, mlx->win, 25, vp+=25, 0xFFFFFF, ft_strjoin("Zoom: ", ft_itoa(mlx->zoom * ZOOM)));


	// mlx_string_put(mlx->mlx, mlx->win, 25, vp+=25, 0xFFFFFF, "Size");
	// mlx_string_put(mlx->mlx, mlx->win, 25, vp+=25, 0xFFFFFF, ft_strjoin("Xmax: ", ft_itoa(mlx->map->width[0])));
	// mlx_string_put(mlx->mlx, mlx->win, 25, vp+=25, 0xFFFFFF, ft_strjoin("Ymax: ", ft_itoa(mlx->map->height)));
	// mlx_string_put(mlx->mlx, mlx->win, 25, vp+=25, 0xFFFFFF, ft_strjoin("Z min: ", ft_itoa(mlx->map->z_min)));
	// mlx_string_put(mlx->mlx, mlx->win, 25, vp+=25, 0xFFFFFF, ft_strjoin("Z max: ", ft_itoa(mlx->map->z_max)));
	// mlx_string_put(mlx->mlx, mlx->win, 25, vp+=25, 0xFFFFFF, ft_strjoin("Rot X: ", ft_itoa(mlx->rot_x)));
	// mlx_string_put(mlx->mlx, mlx->win, 25, vp+=25, 0xFFFFFF, ft_strjoin("Rot Z: ", ft_itoa(mlx->rot_z)));

