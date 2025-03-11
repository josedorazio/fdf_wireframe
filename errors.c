/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:49:11 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/11 19:25:41 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	terminate(int error_code)
{
	if (error_code == 1)
		ft_printf("ERROR: Insert only 1 with '.fdf' extension. \n");
	else if (error_code == 2)
		ft_printf("ERROR: File doesn't exist.\n");
	else if (error_code == 3)
		ft_printf("ERROR: Invalid map\n");
	else if (error_code == 4)
		ft_printf("ERROR: Allocation\n");
	else if (error_code == 5)
		ft_printf("ERROR: Failed Minilibx Init\n");
	exit(EXIT_FAILURE);
}
