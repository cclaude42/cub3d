NAME = cub3D

CC = clang

CFLAGS = -Wall -Wextra -Werror

MLX = minilibx_opengl

LXFLAGS = -lmlx -framework OpenGL -framework AppKit

HEADER = cub3d.h

SRC = cub3d.c \
	parse.c \
	parse_map.c \
	parse_tools.c \
	gnl.c \
	key.c \
	screen.c \
	screen_col.c \
	sprite.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	clang -o $(NAME) -L $(MLX) $(LXFLAGS) $(OBJ)

%.o: %.c
	@echo "\033[0;32mGenerating obj..."
	$(CC) $(CFLAGS) -c $<
	@echo "\033[0m"

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: re
	./$(NAME) tests/map.cub

square: re
	./$(NAME) tests/sqr.cub

norm:
	norminette $(SRC) $(HEADER)

.PHONY: all re clean fclean test sqr norm
