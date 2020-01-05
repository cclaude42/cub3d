NAME = cub3D

CC = clang

CFLAGS = -Wall -Wextra -Werror

MLX = minilibx_opengl

LXFLAGS = -lmlx -framework OpenGL -framework AppKit

HEADER = cub3d.h

SRC = $(addprefix files/, cub3d.c parse.c parse_map.c parse_tools.c \
	parse_check.c gnl.c key.c screen.c screen_col.c sprite.c bitmap.c tools.c)

B_SRC = $(addprefix bonus/, cub3d_bonus.c parse_bonus.c parse_map_bonus.c \
	parse_tools_bonus.c parse_check_bonus.c gnl_bonus.c key_bonus.c \
	screen_bonus.c screen_col_bonus.c sprite_bonus.c bitmap_bonus.c tools_bonus.c)

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re test sqr bmp err inv norm

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[0;33mCompiling..."
	$(CC) -o $(NAME) -L $(MLX) $(LXFLAGS) $(OBJ)
	@echo "\033[0m"

	@echo "\033[0;32mMoving binaries..."
	mkdir -p bin
	mv $(OBJ) bin/
	@echo "\033[0m"

%.o: %.c
	@echo "\033[0;32mGenerating binary..."
	$(CC) $(CFLAGS) -c $<
	@echo "\033[0m"

clean:
	@echo "\033[0;31mCleaning..."
	rm -rf bin
	rm -f bitmap.bmp
	@echo "\033[0m"

fclean: clean
	@echo "\033[0;31mRemoving executable..."
	rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

test: re
	./$(NAME) maps/map.cub

sqr: re
	./$(NAME) maps/sqr.cub

bmp: re
	./$(NAME) maps/map.cub --save

err: re
	./$(NAME) maps/none

inv: re
	./$(NAME) maps/inv.cub

norm:
	norminette $(SRC) $(HEADER)
