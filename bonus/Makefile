NAME = cub3D

CC = clang

CFLAGS = -Wall -Wextra -Werror

MLX = minilibx_opengl

LXFLAGS = -lmlx -framework OpenGL -framework AppKit

HEADER = cub3d.h

B_HEADER = bonus/cub3d_bonus.h

SRC = $(addsuffix .c, cub3d parse parse_map parse_tools parse_check \
						gnl key screen screen_col sprite bitmap tools)

B_SRC = $(addprefix bonus/, $(addsuffix _bonus.c, cub3d parse parse_map \
	parse_tools parse_check gnl key screen screen_col sprite bitmap tools))

OBJ = $(SRC:.c=.o)

B_OBJ = $(B_SRC:.c=.o)

.PHONY: all clean fclean re bonus test sqr bmp err inv norm

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

bonus: fclean $(B_OBJ)
	@echo "\033[0;33mCompiling bonus..."
	$(CC) -o $(NAME) -L $(MLX) $(LXFLAGS) $(B_OBJ)
	@echo "\033[0m"

	@echo "\033[0;32mMoving binaries..."
	mkdir -p bin
	mv $(B_OBJ) bin/
	@echo "\033[0m"

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
