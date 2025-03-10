/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:24:59 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/10 19:52:32 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

int	get_color(int z, t_display *mlx)
{
	float	factor;
	int		z_max;
	int		z_min;

	z_max = mlx->map->z_max;
	z_min = mlx->map->z_min;
	factor = 0.0;
	if (z_max == z_min)
		return 0xFFFFFF;
	factor = (float)(z - z_min) / (z_max - z_min);
	if (factor < 0.25)
		return interpolate_color(0x0000FF, 0x00FF00, factor * 4);
	else if (factor < 0.5)
		return interpolate_color(0x00FF00, 0xFFFF00, (factor - 0.25) * 4);
	else
		return interpolate_color(0xFFFF00, 0xFF0000, (factor - 0.5) * 2);
}

int interpolate_color(int start_color, int end_color, float factor)
{
	int red;
	int green;
	int blue;

	blue = ((1 - factor) * (start_color & 0xFF)) + (factor * (end_color & 0xFF));
	green = ((1 - factor) * ((start_color >> 8) & 0xFF)) + (factor * ((end_color >> 8) & 0xFF));
	red = ((1 - factor) * ((start_color >> 16) & 0xFF)) + (factor * ((end_color >> 16) & 0xFF));
	return (red << 16) | (green << 8) | blue;
}
