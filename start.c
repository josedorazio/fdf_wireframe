/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:50:21 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/10 00:03:37 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	init_display_mlx(t_display *mlx)
{
	mlx->mlx = mlx_init();
	mlx->img = (t_image *)ft_calloc(1, sizeof(t_image));  // or a similar initialization
	mlx->img->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->img->addr = mlx_get_data_addr(mlx->img->img, &mlx->img->bits_per_pixel,
			&mlx->img->line_length, &mlx->img->endian);
	mlx->img->width = WIDTH;  // Usa el valor predeterminado de la ventana
	mlx->img->height = HEIGHT; // Usa el valor predeterminado de la ventana
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "FDF - Wireframe");
	return (0);
}

int	set_display_default(t_display *mlx, t_map *map)
{
	int	max_size;

	mlx->map = map;
	mlx->map = map;
	max_size = map->height;
	if (map->width > map->height)
		max_size = map->width;
	printf("Max size %d\n", max_size);
	mlx->zoom = (WIDTH / max_size) * 0.4; 
	mlx->rot_x = 0;
	mlx->rot_y = 0.0;
	mlx->rot_z = 0;
	return (0);
}

// int handle_resize(int width, int height, t_display *mlx)
// {
//     if (!mlx || !mlx->map || !mlx->img) {
//         printf("Error: Invalid pointers in handle_resize\n");
//         return (0); // Manejo de error apropiado
//     }

//     // Calcular el factor de escala basándote en el tamaño de la ventana
//     printf("Map Width: %d, Map Height: %d\n", mlx->map->width, mlx->map->height);
//     int max_size = (mlx->map->width > mlx->map->height) ? mlx->map->width : mlx->map->height;
//     float new_zoom = (width / max_size) * 0.4; // Ajusta este valor para obtener la escala deseada

//     // Verificar si la nueva escala es diferente de la anterior
//     if (new_zoom != mlx->zoom) {
//         mlx->zoom = new_zoom;
//     }

//     // Actualiza las dimensiones de la imagen
//     mlx->img->width = width;
//     mlx->img->height = height;

//     // Redibuja la ventana con el nuevo tamaño y la nueva escala
//     if (!mlx->mlx || !mlx->win) {
//         printf("Error: Invalid window pointer\n");
//         return (0); // Manejo de error adecuado
//     }

//     mlx_clear_window(mlx->mlx, mlx->win);  // Limpiar la ventana
//     draw_map(mlx);  // Volver a dibujar la imagen con las nuevas dimensiones y escala

//     return (0);
// }

void	system_init(t_map *map)
{
	t_display	*mlx;

	ft_printf("Initializing Minilibx...\n");
	mlx = (t_display *)ft_calloc(1, sizeof(t_display));
	if (!mlx)
		terminate(33, NULL);
	if (set_display_default(mlx, map) == 1)
	{
		free_mlx_map(mlx);
		free_map(map);
		exit(EXIT_FAILURE);
	}
	printf("Starting Init Display MLX\n");
	if (init_display_mlx(mlx) == 1)
	{
		free_mlx_map(mlx);
		free_map(map);
		exit(EXIT_FAILURE);
	}
	//mlx_hook(mlx->win, 12, 1L << 15, handle_resize, mlx);
	mlx_hook(mlx->win, KP, (1L<<0), key_hook, mlx);
	mlx_hook(mlx->win, DN, (1L<<17), free_close, mlx);
	draw_map(mlx);
	mlx_loop(mlx->mlx);
	free_mlx_map(mlx);
	free(mlx);
}


/*
1. Corregir primero el boton de maximizar
2. Corregir el problema al graficar la imagen t1 y t2
3. Me falta agregar un gradiente para identificar la altura de los puntos.
4. Si tengo tiempo agregar alguna otra funcionalidad. (NO ES NECESARIO)
*/
