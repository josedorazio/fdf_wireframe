/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:17:04 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/08 13:40:47 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int	main(int ac, char **av)
{
	t_map	map;

	
	if (ac != 2)
		terminate(1, NULL);
	load_map(av[1], &map);
	printf("Starting System Init\n");
	system_init(&map);
	free_map(&map);
	return (0);
}




