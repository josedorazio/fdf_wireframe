/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:15:39 by jdorazio          #+#    #+#             */
/*   Updated: 2025/02/11 16:39:35 by jdorazio         ###   ########.fr       */
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

// Medidas de la interfaz
# define WIDTH 1920
# define HEIGHT 1080
# define HEIGHT_SCALE 100
# define SCALE 10
# define M_PI 3.14159265358979323846

typedef struct s_map
{
	int	height;
	int	*width;
	int	**matrix;
}	t_map;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;

}	t_point;

typedef struct t_delta
{
	int	dx;
	int	dy;
	int	sign_x;
	int	sign_y;
}	t_delta;



typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;


typedef struct s_display
{
	void	*mlx;
	void	*win;
	t_data	img;
	t_map	map;
}	t_display;




// MAIN FILE

// #----------# Program #----------#
int	main(int ac, char **av);
// #----------#  #----------#

// #----------# Error Handling #----------#
int	terminate(int error_code);
// #----------#  #----------#

// #----------# VALIDATE #----------#
int	validate(char *num);
int	convert(char *num);
int	ft_is_sign(char c);

// #----------# MAP INIT #----------#
void	load_map(char *file, t_map *map);
void	fill_matrix(int fd, t_map *map);
void	map_init(char *file, t_map *map);
void	map_dimensions(char *file, t_map *map);

// #----------# MAP INIT UTILS #----------#
void	vertical_dim(char *file, t_map *map);
void	horizontal_dim(int fd, t_map *map);
char	*clear_line(int fd);


// #----------# START #----------#
void	system_init(t_map *map);
int	init_display_mlx(t_map *map, t_display *mlx);




// #----------# PROJECTION #----------#
void	draw_map(t_display *mlx);
void	bresenham_line(t_display *mlx, t_point p1, t_point p2);
t_point	create_point(int x, int y, t_display *mlx);
void	isometric(t_point *p);


#endif
