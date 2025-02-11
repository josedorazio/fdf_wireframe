/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:17:04 by jdorazio          #+#    #+#             */
/*   Updated: 2025/02/10 22:15:30 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int	main(int ac, char **av)
{
	t_map	map;

	if (ac != 2)
		terminate(1);
	load_map(av[1], &map);


	printf("Starting System Init\n");
	system_init(&map);
	
	printf("Working\n");
    // Free memory
    for (int i = 0; i < map.height; i++)
        free(map.matrix[i]);
    free(map.matrix);


	return (0);
}



