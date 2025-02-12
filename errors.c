/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:49:11 by jdorazio          #+#    #+#             */
/*   Updated: 2025/02/12 19:02:03 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

int	terminate(int error_code, void *ptr)
{
	if (error_code == 1) // missing inputs
		ft_printf("NOT ENOUGH INPUTS\n"); //not an fdf file
	else if (error_code == 2)
		ft_printf("NOT AN .fdf file\n");
	else if (error_code == 3)
		// FAILS TO REED FILE
		free(ptr);
	else if (error_code == 4)  // Free maps
		free_map(ptr);
	else if (error_code == 5)
		free(ptr);
	else if (error_code == 6)
		free_close(ptr);
	else if (error_code == 7)
		ft_printf("Failed Isometric Projection \n");
	exit(EXIT_FAILURE);
}

/* me falta un free para fd, que en realidad 
lo que liberaria es FILE

*/
