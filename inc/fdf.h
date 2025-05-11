/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:15:39 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/12 16:15:55 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <math.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "libft/libft.h"
# include "resources/minilibx-linux/mlx.h"
# include "keybindings.h"

// Medidas de la interfaz
# define WIDTH 1920
# define HEIGHT 1080
# define SIDEBAR 350
# define M_PI 3.14159265358979323846
# define ANGLE 0.523599

typedef struct s_map
{
	int	height;
	int	width;
	int	z_max;
	int	z_min;
	int	**color;
	int	**matrix;
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

typedef struct s_delta
{
	int	dx;
	int	dy;
	int	sign_x;
	int	sign_y;
}	t_delta;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

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
}	t_display;

// MAIN FILE

// #----------# Program #----------#
int			main(int ac, char **av);
// #----------#  #----------#
// #----------# Error Handling #----------#
int			terminate(int error_code);
// #----------#  #----------#
// #----------# VALIDATE #----------#
int			ft_is_sign(char c);
int			validate(char *num);
int			ft_atoi_base(char *color_str);
void		convert(char *str, int *z, int *color);
// #----------# MAP INIT #----------#
int			map_init(char *file, t_map *map);
int			init_matrix(t_map *map);
int			fill_matrix(int fd, t_map *map);
void		load_map(char *file, t_map *map);
// #----------# MAP INIT UTILS #----------#
int			check_extension(char *file);
int			get_height(char *file, t_map *map);
int			data_counter(char *line);
int			get_width(char *file, t_map *map);
void		z_values(t_map *map);
// #----------# START #----------#
void		system_init(t_map *map);
int			set_display_default(t_display *mlx, t_map *map);
int			init_display_mlx(t_display *mlx);
// #----------# PROJECTION #----------#
void		draw_map(t_display *mlx);
void		bresenham_line(t_display *mlx, t_point p1, t_point p2);
void		init_bresenham_line(t_point *p1, t_point *p2, t_delta *delta);
t_point		create_point(int x, int y, t_display *mlx);
void		isometric(t_point *p, t_display *mlx);
void		put_pixel(t_display *mlx, int x, int y, int color);
void		rot_x(t_point *p, float angle);
void		rot_y(t_point *p, float angle);
void		rot_z(t_point *p, float angle);
// # ---------# KEY EVENT #----------#
int			key_hook(int keycode, t_display *mlx);
int			free_close(t_display *mlx);
void		free_display(t_display *mlx);
void		free_map(t_map *map);
void		free_array(char **arr);
// #----------# SIDEBAR #----------#
void		draw_sidebar(t_display *mlx);
void		sidebar_description(t_display *mlx);
void		update_rot(int keycode, t_display *mlx);
void		free_mlx_map(t_display *mlx);
// #----------# SIDEBAR #----------#
int			get_color(int z, t_display *map);
int			interpolate_color(int start_color, int end_color, float factor);

#endif
