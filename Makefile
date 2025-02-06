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

SRCS = main.c

OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a
GNL = get_next_line/gnl.a
PRINTF = printf/ft_printf.a

ifeq ($(UNAME_S),Linux)
	MINILIBX_DIR	:= $(LIB)minilibx/minilibx_linux/
	#MINILIBX		:= $(MINILIBX_DIR)libmlx.a
	MINILIBXCC		:= -I$(MINILIBX_DIR) -L $(MINILIBX_DIR) -lmlx
	LIBS			:= -lXext -lX11 -lm
else ifeq ($(UNAME_S),Darwin)
	MINILIBX_DIR	:= $(LIB)minilibx/minilibx_macos/
	#MINILIBX		:= $(MINILIBX_DIR)libmlx.a
	MINILIBXCC		:= -I$(MINILIBX_DIR) -L $(MINILIBX_DIR) -lmlx
	LIBS			:= -framework OpenGL -framework AppKit
endif


CC = cc
CFLAGS = -Wall -Werror -Wextra
# -fsanitize=address
AR = ar rcs

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(GNL) $(PRINTF) $(MINILIBXCC)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(GNL) $(PRINTF) $(MINILIBXCC) -o $(NAME)
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
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

$(MINILIBXCC):
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
