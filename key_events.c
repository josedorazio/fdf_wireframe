/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 22:57:25 by jdorazio          #+#    #+#             */
/*   Updated: 2025/02/11 23:47:34 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"




int	key_hook(int keycode, t_display *mlx)
{
	if (keycode == 53)
	{
		printf("Debug ESC\n");
		free_close(mlx);
	}
	return (0);
}

