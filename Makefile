# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dsalaman <dsalaman@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/07 08:57:54 by dsalaman      #+#    #+#                  #
#    Updated: 2020/07/09 13:54:04 by dsalaman      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC = main.c

OBJECTS = $(SRC:.c=.o)

EXT_LIB = libft/libft.a mlx/libmlx.dylib gnl/libgnl.a

FLAGS= -Wall -Wextra -Werror -O3 -g

MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit

BMP = screenshot.bmp

HEADERS = cub3D.h

INC = -Ilibft -Imlx -Ignl

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -C libft
	@make -C gnl
	@make -C mlx
	@cp mlx/libmlx.dylib .
	@gcc $(FLAGS)$(INC)$(MLX_FLAGS) -o $(NAME)$(OBJECTS)$(EXT_LIB)
	@cp mlx/libmlx.dylib .
	
%.o: %.c $(HEADERS)
	@gcc $(FLAGS) $(INC) -c $< -o $@
	@echo "cub3D successful creation"


clean:
	@rm -f $(OBJECTS)
	@make clean -C libft
	@make clean -C mlx
	@make clean -C gnl
	@rm -f .DS_Store
	@echo "Objects file were removed - clean."

fclean: clean
	@rm -f $(NAME)
	@rm -f libmlx.dylib
	@make fclean -C libft
	@make fclean -C mlx
	@make fclean -C gnl
	@rm -f .DS_Store
	@echo "Objects file were removed - fclean."

re: fclean all

.PHONY: all clean fclean re
