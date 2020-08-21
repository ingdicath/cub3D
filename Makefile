# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dsalaman <dsalaman@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/07 08:57:54 by dsalaman      #+#    #+#                  #
#    Updated: 2020/08/21 17:19:43 by dsalaman      ########   odam.nl          #
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

LIBFT = libft.a

BMP = cub3d_screenshot.bmp

SRC = parsing/check_args_path.c parsing/check_textures_path.c\
	parsing/check_res_floor_ceiling_color.c parsing/read_map.c\
	parsing/check_orientacion.c parsing/fill_elements.c\
	parsing/initialize_structures.c raycasting/game_start.c\
	raycasting/set_game.c raycasting/render_map.c\
	raycasting/calculate_wall_draw.c raycasting/draw_walls.c\
	raycasting/movements.c raycasting/rotations.c\
	raycasting/keys_actions.c raycasting/draw_floor_ceiling.c\
	raycasting/screenshot.c raycasting/write_bytes.c main.c

OBJECTS = $(SRC:.c=.o)

all: $(NAME)

$(LIB_FT):
	@make -C $(LIB_FT)
	@cp $(LIB_FT)/$(LIBFT) .
	@echo "libft library created successfully"

$(LIBMLX):
	@make -C $(MLX)
	@cp $(MLX)/$(LIBMLX) .
	@echo "mlx library created successfully"

$(NAME): $(OBJECTS) $(LIBMLX) $(LIB_FT)
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
