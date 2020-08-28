# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dsalaman <dsalaman@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/07 08:57:54 by dsalaman      #+#    #+#                  #
#    Updated: 2020/08/28 10:05:05 by dsalaman      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

HEADERS = cub3d.h

CC = gcc

FLAGS = -Wall -Wextra -Werror

MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

MLX = mlx

LIBMLX = libmlx.dylib

LIB_FT = libft

LIB = lib_ft

LIBFT = libft.a

BMP = cub3d_screenshot.bmp

SRC = parsing/check_args_path.c parsing/check_textures_path.c\
	parsing/check_res_floor_ceiling_color.c parsing/read_map.c\
	parsing/check_orientacion.c parsing/fill_elements.c\
	parsing/initialize_structures.c raycasting/start_game.c\
	raycasting/set_game.c raycasting/render_map.c\
	raycasting/render_walls.c raycasting/drawer.c\
	raycasting/movements.c raycasting/set_utils.c raycasting/sprite_utils.c\
	raycasting/actions.c raycasting/render_floor_ceiling.c\
	raycasting/screenshot.c raycasting/write_bytes.c main.c\
	raycasting/render_sprites.c parsing/check_map.c\
	

OBJECTS = $(SRC:.c=.o)

all: $(NAME)

$(LIB):
	@make -C $(LIB_FT)
	@cp $(LIB_FT)/$(LIBFT) .
	@echo "libft library created successfully"

$(LIBMLX):
	@make -C $(MLX)
	@cp $(MLX)/$(LIBMLX) .
	@echo "mlx library created successfully"

$(NAME): $(OBJECTS) $(LIBMLX) $(LIB)
	@$(CC) $(FLAGS) $(MLX_FLAGS) -o $(NAME) $(OBJECTS) $(LIBFT)
	@echo "name rule executed successfully"

%.o: %.c $(HEADERS)
	@$(CC) $(FLAGS) -Imlx -Ilibft -c $< -o $@

clean:
	@rm -f $(OBJECTS) $(LIBMLX) $(BMP)
	@make clean -C $(MLX)
	@make clean -C $(LIB_FT)
	@rm -f .DS_Store
	@echo "Objects file were removed - clean."

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIB_FT)	
	@echo "Objects file were removed - fclean."

sclean: 
	@rm -f $(OBJECTS) $(BMP)
	@echo "Objects file were removed - sclean."

cub: sclean $(NAME)

re: fclean all

.PHONY: all clean fclean re cub
