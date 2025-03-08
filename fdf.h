/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:15:39 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/08 13:11:31 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_h
# define FDF_h

# include <unistd.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <math.h>

# include "libft/libft.h"
# include "printf/ft_printf.h"
# include "get_next_line/get_next_line.h"
# include "minilibx/mlx.h"
# include "keybindings.h"

// Medidas de la interfaz
# define WIDTH 1920
# define HEIGHT 1080
# define SIDEBAR 350
# define M_PI 3.14159265358979323846
# define ZOOM 10

typedef struct s_map
{
	int	height;
	int	width;
	int	color;
	int	**matrix;
	int	z_max;
	int	z_min;
}	t_map;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
	int	sx;
	int	sy;

}	t_point;

typedef struct t_delta
{
	int	dx;
	int	dy;
	int	sign_x;
	int	sign_y;
}	t_delta;

typedef struct	s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}		t_image;


typedef struct s_display
{
	void	*mlx;
	void	*win;
	t_image	*img;
	t_map	*map;
	float	zoom;
	float	rot_x;
	float	rot_y;
	float	rot_z;
	float	angle;
}	t_display;


// typedef struct s_point
// {
//     int x;         // Coordenada x
//     int y;         // Coordenada y
//     int z;         // Coordenada z (altura)
//     int color;     // Color del punto
//     int sx;        // Coordenada proyectada en pantalla (x)
//     int sy;        // Coordenada proyectada en pantalla (y)
//     int dx;        // Diferencia x para trazado de líneas
//     int dy;        // Diferencia y para trazado de líneas
//     int sign_x;    // Dirección en x
//     int sign_y;    // Dirección en y
// } t_point;

// typedef struct s_map
// {
//     int      height;   // Número de filas en el mapa
//     int      width;    // Número de columnas en el mapa
//     t_point  **matrix; // Matriz 2D de puntos
//     int      z_max;    // Máxima altura
//     int      z_min;    // Mínima altura
// } t_map;

// typedef struct s_display
// {
//     void    *mlx;            // Referencia al contexto de MLX
//     void    *win;            // Referencia a la ventana de MLX
//     void    *img;            // Imagen renderizada (MLX)
//     char    *addr;           // Dirección de memoria para la imagen
//     int     bits_per_pixel;  // Bits por píxel
//     int     line_length;     // Tamaño de cada fila de la imagen
//     int     endian;          // Orden de los bytes
//     t_map   *map;            // Mapa asociado
//     float   zoom;            // Nivel de zoom
//     float   rot_x;           // Rotación en el eje X
//     float   rot_y;           // Rotación en el eje Y
//     float   rot_z;           // Rotación en el eje Z
// } t_display;




// MAIN FILE

// #----------# Program #----------#
int	main(int ac, char **av);
// #----------#  #----------#

// #----------# Error Handling #----------#
int	terminate(int error_code, void *ptr);
// #----------#  #----------#

// #----------# VALIDATE #----------#
int	validate(char *num);
int	convert(char *num);
int	ft_is_sign(char c);

// #----------# MAP INIT #----------#
void	load_map(char *file, t_map *map);
int		map_init(char *file, t_map *map);
int		map_dimensions(char *file, t_map *map);
int		fill_matrix(int fd, t_map *map);
void	z_values(t_map *map);

// #----------# MAP INIT UTILS #----------#
int		get_height(char *file, t_map *map);
int		horizontal_dim(int fd, t_map *map);
int		get_width(char *file, t_map *map);

char	*trim_newline(int fd);

// #----------# START #----------#
void	system_init(t_map *map);
int	set_display_default(t_display *mlx, t_map *map);
int		init_display_mlx(t_display *mlx);

// #----------# PROJECTION #----------#
void	draw_map(t_display *mlx);
void	bresenham_line(t_display *mlx, t_point p1, t_point p2);
void	init_bresenham_line(t_point *p1, t_point *p2, t_delta *delta);
t_point	create_point(int x, int y, t_display *mlx);
void	isometric(t_point *p, t_display *mlx);
void	put_pixel(t_display *mlx, int x, int y, int color);
void	rot_x(t_point *p, float angle);
void	rot_z(t_point *p, float angle);

// #----------# KEY EVENT #----------#
int		key_hook(int keycode, t_display *mlx);
int		free_close(t_display *mlx);
void	free_display(t_display *mlx);
void	free_map(t_map *map);
void	free_array(char **arr);

// #----------# SIDEBAR #----------#
void	draw_sidebar(t_display *mlx);
void	sidebar_description(t_display *mlx);
void	update_rot(int keycode, t_display *mlx);


void	free_mlx_map(t_display *mlx);

#endif
