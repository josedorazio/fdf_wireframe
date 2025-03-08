/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:17:04 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/08 16:31:39 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int	main(int ac, char **av)
{
	t_map	map;


	if (ac != 2)
		terminate(1, NULL);
	ft_printf("Loading Map\n");
	load_map(av[1], &map);
	ft_printf("Starting System Init\n");
	system_init(&map);
	free_map(&map);
	return (0);
}




