# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 15:33:02 by jdorazio          #+#    #+#              #
#    Updated: 2024/09/30 09:11:56 by jdorazio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

#  find *.c | xargs echo

SRCS = src/color.c src/draw.c src/draw_sidebar.c src/draw_utils.c src/errors.c src/free_fn.c src/key_events.c src/main.c src/map_init.c src/map_init_utils.c src/start.c src/validate.c

OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a
MLX_A = minilibx-linux/libmlx.a

CC = cc
CFLAGS = -Wall -Werror -Wextra -fPIC \
		-Iinc \
		-Ilibft \
		-Iresources/minilibx-linux
#-g3 -fsanitize=address
AR = ar rcs
MLX_FLAGS = -Lresources/minilibx-linux -lmlx -lX11 -lXext -lm

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_A)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -no-pie -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -Iminilibx-linux -c $< -o $@
	@echo "Compiled $<."

$(LIBFT):
	make -C libft
	@echo "Compiled libft"

$(MLX_A):
	make -C resources/minilibx-linux
	@echo "Compiled MINILIBX"

clean:
	make -C resources/minilibx-linux clean
	make -C libft clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(LIBFT) libmlx.a

re: fclean all

.PHONY: all clean fclean re
