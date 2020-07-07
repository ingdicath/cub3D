# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dsalaman <dsalaman@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/07 08:57:54 by dsalaman      #+#    #+#                  #
#    Updated: 2020/07/07 14:05:06 by dsalaman      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

FLAGS= -Wall -Wextra -Werror

MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

SRC = ft_atoi.c

OBJECTS= $(SRC:.c=.o)

LIBFT = libft.a

MLX = libmlx.dylib

all: $(NAME)

libft.a: 
	@cd libft && make

libmlx.dylib: 
	@cd mlx && make && mv $(MLX)..

$(NAME): $(LIBFT) $(MLX) $(OBJECTS)
	@gcc $(FLAGS)$(MLX_FLAGS) -o $(NAME)$(OBJECTS) ./libft/$(LIBFT) 
	
%.o:%.c
	@gcc $(FLAGS) -lmlx -linc -llibft -c $< -o $@ 
	@echo "cub3D successful creation"

$(OBJECTS): $(SRC)
	@gcc -c $(FLAGS) $(SRC)

clean:
	@rm -f $(OBJECTS)
	@rm -f *.o
	@rm -f *~
	@rm -f ./*/*/*.o
	@rm -f .DS_Store
	@echo "Objects file were removed."

fclean: clean
	@rm -f $(NAME) $(MLX)
	@cd ./libft && make fclean

re: fclean all

.PHONY: all clean fclean re
