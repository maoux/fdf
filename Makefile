# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heynard <heynard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/12 15:01:03 by heynard           #+#    #+#              #
#    Updated: 2017/06/05 16:15:51 by heynard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = gcc

FLAGS = -Wall -Wextra -Werror

FLAGS_MLX = -framework OpenGL -framework AppKit -lmlx -L ./libft/ -lft

PATH_SRCS = ./srcs/

SRC_FILES = fdf_main.c\
			fdf_handle_image.c\
			fdf_handle_event.c\
			fdf_draw_line.c\
			fdf_term_print.c\
			fdf_free_env.c\
			fdf_parse_map.c\
			fdf_draw_tab.c\
			fdf_min_max.c

SRCS = $(addprefix $(PATH_SRCS), $(SRC_FILES))

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ./libft/
	@$(CC) $(FLAGS) $(FLAGS_MLX) $^ -o $(NAME)
	@echo "\033[1;34mfdf\t\t\033[1;33mBuilding\t\t\033[0;32m[OK]\033[0m"

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: all clean fclean re

clean:
	@make -C ./libft/ clean
	@rm -f $(OBJ)
	@echo "\033[1;34mfdf\t\t\033[1;33mCleaning objects\t\033[0;32m[OK]\033[0m"

fclean: clean
	@make -C ./libft/ fclean
	@rm -f $(NAME)
	@echo "\033[1;34mfdf\t\t\033[1;33mCleaning fdf\t\t\033[0;32m[OK]\033[0m"

re: fclean all
