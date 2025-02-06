/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:54:57 by jdorazio          #+#    #+#             */
/*   Updated: 2025/02/06 14:37:51 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <ctype.h>
# include <aio.h>
# include <stdlib.h>
# include <limits.h>
# include <stdarg.h>
#include "../libft/libft.h"

size_t	ft_strlen_pf(const char *s);
int		ft_putchar_fd_pf(char c, int fd);
int		ft_putstr_fd_pf(char *s, int fd);
int		ft_putnbr_fd_pf(long n, int fd);
int		ft_putnbr_base_pf(unsigned long n, char *base);
int		ft_printf(char const *c, ...);

#endif
