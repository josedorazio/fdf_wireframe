/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:24:17 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/10 20:24:33 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rot_x(t_point *p, float angle)
{
	int	y;
	int	z;

	angle += 0;
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
