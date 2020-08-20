# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dsalaman <dsalaman@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/07 08:57:54 by dsalaman      #+#    #+#                  #
#    Updated: 2020/08/20 18:37:34 by dsalaman      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIB = libcub3d.a

HEADERS = cub3d.h 

FLAGS= -Wall -Wextra -Werror

MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit

#GNL = gnl
MLX = mlx
#LIBGNL = libgnl.a
LIB_FT = libft

LIBFT = libft.a

LIBMLX = libmlx.dylib

BMP = cub3d_screenshot.bmp

SRC = ft_split.c parsing.c start_game.c cub3d_utils.c

OBJECTS = $(SRC:.c=.o)

all: $(NAME)

$(LIBMLX):
	@make -C $(MLX)
	@cp $(MLX)/$(LIBMLX) .

$(LIBFT):
	@make -C $(LIB_FT)
	@cp $(LIB_FT)/$(LIBFT) .
#$(LIBGNL):
	#@make -C $(GNL)
	#@cp $(GNL)/$(LIBGNL) .

$(NAME): $(OBJECTS) $(LIBMLX) $(LIBFT)
	@ar rcs $(LIB) $(OBJECTS)
	@gcc -I $(MLX) -L $(MLX) $(MLX_FLAGS) $(LIB) $(LIBFT) -o $(NAME)

#$(NAME): $(OBJECTS) $(LIBMLX) $(LIBGNL)
#	@ar rcs $(LIB) $(OBJECTS)
#	@gcc -I $(MLX) -L $(MLX) $(MLX_FLAGS) $(LIB) $(LIBGNL) -o $(NAME)

	#libgnl.a
%.o: %.c $(HEADERS)
	@gcc $(FLAGS) -c $< -o $@
	@echo "cub3D successful creation"

clean:
	@rm -f $(OBJECTS) $(LIBMLX) $(BMP)
	@make clean -C $(MLX)
	@make clean -C $(LIB_FT)
	@rm -f .DS_Store
	@echo "Objects file were removed - clean."

fclean: clean
	@rm -f $(NAME)$(LIB)
	@make fclean -C $(LIB_FT)	
	@echo "Objects file were removed - fclean."

re: fclean all

.PHONY: all clean fclean re
