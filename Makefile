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

SRCS = srcs/color.c srcs/draw.c srcs/draw_sidebar.c srcs/draw_utils.c srcs/errors.c\
	srcs/free_fn.c srcs/key_events.c srcs/main.c srcs/map_init.c srcs/map_init_utils.c srcs/start.c srcs/validate.c

OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a
MLX_DIR = resources/minilibx-linux
MLX_A = $(MLX_DIR)/libmlx.a

CC = cc
CFLAGS = -Wall -Werror -Wextra -fPIC -Iinc -Ilibft -I$(MLX_DIR)
#-g3 -fsanitize=address 
AR = ar rcs
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_A)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -no-pie -o $(NAME)
	@echo "Executable $(NAME) built."
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $<."

$(LIBFT):
	make -C libft
	@echo "Compiled libft"

$(MLX_A):
	make -C $(MLX_DIR)
	@echo "Compiled MINILIBX"

clean:
	make -C $(MLX_DIR) clean
	make -C libft clean
	rm -f $(OBJS)
	@echo "Cleaned object files."

fclean: clean
	rm -f $(NAME) $(LIBFT) libmlx.a
	@echo "Removed executable."

re: fclean all

.PHONY: all clean fclean re
