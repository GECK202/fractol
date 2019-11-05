# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkaron <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/23 17:12:18 by vkaron            #+#    #+#              #
#    Updated: 2019/11/05 22:05:35 by vkaron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re, libr

FLAGS = -Wall -Wextra -Werror -g

C_FILES = 	fractol.c init.c events.c set_color.c calculate.c threads.c\
			mandelbrot.c

O_FILES = $(C_FILES:.c=.o)

H_DIR = -Ilibft/Includes -Ilibmat3d

NAME = fractol

all: $(NAME)

$(NAME): $(O_FILES)
	gcc $(FLAGS) -o $@ $^ $(H_DIR) -lpthread -lmlx -framework OpenGL -framework AppKit

%.o: %.c fractol.h
	gcc $(FLAGS) -c $< $(H_DIR)

clean:
	rm -f $(O_FILES)

fclean : clean
	rm -f $(NAME)

re: fclean all
