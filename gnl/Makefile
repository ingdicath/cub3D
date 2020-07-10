# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: dsalaman <dsalaman@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/09 07:51:23 by dsalaman      #+#    #+#                  #
#    Updated: 2020/07/09 07:51:28 by dsalaman      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libgnl.a

SRC = get_next_line.c get_next_line_utils.c

OBJECTS = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECTS)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)
	@echo "gnl library created"

%.o: %.c
	@echo "gnl  compiling $<"
	@gcc $(FLAGS) -c -o $@ $<

clean: 
	@rm -f $(OBJECTS)
	@echo "Objects files were removed."

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
