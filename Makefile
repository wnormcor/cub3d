# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wnormcor <wnormcor@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/16 10:18:16 by wnormcor          #+#    #+#              #
#    Updated: 2020/10/27 16:22:02 by wnormcor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC = src/cub3d.c \
	src/parser.c \
	src/load_data.c \
	src/set_param.c \
	src/init_param.c \
	src/move_player.c \
	src/key_func.c \
	src/check.c \
	src/make_screen.c \
	src/screen_utils.c \
	src/draw_items.c \
	src/load_xpm.c \
	src/save_bmp.c \
	src/error_close.c

%.o: %.c $(HEAD)
	gcc -Wall -Wextra -Werror -c -g $< -o $@

OBJ = $(SRC:%.c=%.o)

$(NAME): $(OBJ)
	@$(MAKE) -C ./libft
	@$(MAKE) -C ./minilibx
	gcc -Wall -Wextra -Werror -g -o $(NAME) $(OBJ) -L ./minilibx -lmlx -framework OpenGL -framework AppKit ./libft/libft.a
	@echo Cub3D created

all: $(NAME)

clean:
	@$(MAKE) clean -C ./libft
	@$(MAKE) clean -C ./minilibx
	@rm -f $(OBJ)
	@echo CLEAN: Objects with LIBFT files .o had been cleaned

fclean: clean
	@$(MAKE) fclean -C ./libft
	@rm -f $(NAME)
	@echo FCLEAN: Library $(NAME) has been cleaned

re: fclean all
	@echo RE: fclean and make all completed

.PHONY: all clean fclean re bonus
