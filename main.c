/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:17:04 by jdorazio          #+#    #+#             */
/*   Updated: 2025/02/26 18:50:01 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int	main(int ac, char **av)
{
	t_map	map;

	if (ac != 2)
		return (1);
	load_map(av[1], &map);
	printf("Starting System Init\n");
	system_init(&map);

	// FREE MEMORY
	free_map(&map);

	return (0);
}



