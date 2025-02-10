# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 15:33:02 by jdorazio          #+#    #+#              #
#    Updated: 2024/09/28 15:48:26 by jdorazio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gnl.a

#  find *.c | xargs echo

SRCS =  get_next_line.c get_next_line_utils.c
SRCS_BONUS = get_next_line_bonus.c get_next_line_utils_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)


LIBFT = ../libft/libft.a

CC = cc
CFLAGS = -Wall -Werror -Wextra -D BUFFER_SIZE=42

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
		ar rcs $(NAME) $(OBJS) $(LIBFT) -o $(NAME)

bonus: $(OBJS) $(OBJS_BONUS)
		$(CC) $(OBJS) $(OBJS_BONUS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft
	@echo "Compiled libft"

clean:
	rm -f $(OBJS) $(OBJS_BONUS)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
