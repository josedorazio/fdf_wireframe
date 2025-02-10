/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:49:11 by jdorazio          #+#    #+#             */
/*   Updated: 2025/02/10 22:14:19 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

int	terminate(int error_code)
{
	if (error_code == 1)
		ft_printf("NOT ENOUGH INPUTS\n");
	else if (error_code == 2)
		ft_printf("NOT AN .fdf file\n");
	else if (error_code == 3) 
		ft_printf("NOT CREATED\n");
	else if (error_code == 4)
		ft_printf("Map has a non-numerical character\n");
	else if (error_code == 5)
		ft_printf("mlx failed to execute\n");
	else if (error_code == 6)
		ft_printf("Failed Isometric Projection \n");
	exit(EXIT_FAILURE);
}
