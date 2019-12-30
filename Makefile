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
	bitmap.c \
	tools.c \

OBJ = $(SRC:.c=.o)

.PHONY: all re clean fclean test sqr bmp norm

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) -L $(MLX) $(LXFLAGS) $(OBJ)
	mkdir -p bin
	mv $(OBJ) bin/

%.o: %.c
	@echo "\033[0;32mGenerating obj..."
	$(CC) $(CFLAGS) -c $<
	@echo "\033[0m"

clean:
	rm -rf bin

fclean: clean
	rm -f $(NAME)

re: fclean all

test: re
	./$(NAME) maps/map.cub

sqr: re
	./$(NAME) maps/sqr.cub

bmp: re
	./$(NAME) maps/map.cub --save

norm:
	norminette $(SRC) $(HEADER)
