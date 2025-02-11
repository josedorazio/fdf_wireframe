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

NAME = FDF

#  find *.c | xargs echo

SRCS = errors.c free_fn.c key_events.c main.c map_init.c map_init_utils.c start.c validate.c

OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a
PRINTF = printf/ft_printf.a
GNL = get_next_line/gnl.a
MLX_A = minilibx/libmlx.a

CC = cc
CFLAGS = -Wall -Werror -Wextra -fPIC 
# -fsanitize=address
AR = ar rcs
MLX_FLAGS = -Lminilibx -lmlx -lX11 -lXext -lm

all: $(NAME)

$(NAME): $(OBJS) $(GNL) $(LIBFT)  $(PRINTF) $(MLX_A)
		$(CC) $(CFLAGS) $(OBJS) $(GNL) $(LIBFT)  $(PRINTF) $(MLX_FLAGS) -no-pie -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -Iminilibx -c $< -o $@
	@echo "Compiled $<."

$(LIBFT):
	make -C libft
	@echo "Compiled libft"
$(GNL):
	make -C get_next_line
	@echo "Compiled GNL"

$(PRINTF):
	make -C printf
	@echo "Compiled PRINTF"

$(MLX_A):
	make -C minilibx
	@echo "Compiled MINILIBX"

clean:
	rm -f $(OBJS)
	make clean -C libft
	make clean -C get_next_line
	make clean -C ft_printf
	make clean -C minilibx


fclean: clean
	rm -f $(NAME)
	make fclean -C libft
	make fclean -C get_next_line
	make fclean -C ft_printf
	make fclean -C minilibx

re: fclean all

.PHONY: all clean fclean re
