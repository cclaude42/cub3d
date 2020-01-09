NAME = cub3D

CC = clang

CFLAGS = -Wall -Wextra -Werror

MLX = mlxopengl

LXFLAGS = -lmlx -framework OpenGL -framework AppKit

HEADER = cub3d.h

B_HEADER = cub3d_bonus.h

SRC = cub3d \
	parse \
	parse_map \
	parse_tools \
	parse_check \
	gnl \
	key \
	screen \
	screen_col \
	sprite \
	bitmap \
	tools \

FIL = $(addsuffix .c, $(addprefix files/, $(SRC)))

OBJ = $(FIL:.c=.o)

BIN = $(addsuffix .o, $(SRC))

B_HEADER = cub3d_bonus.h

B_SRC = screen_row \
	sprite_draw \
	key_more \
	weapons \
	hud \

B_FIL = $(addsuffix _bonus.c, $(addprefix bonus/, $(SRC) $(B_SRC)))

B_OBJ = $(B_FIL:.c=.o)

B_BIN = $(addsuffix _bonus.o, $(SRC) $(B_SRC))

.PHONY: all clean fclean re bonus test sqr bmp err inv norm

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[0;33mCompiling..."
	$(CC) -o $(NAME) -L $(MLX) $(LXFLAGS) $(BIN)
	@echo "\033[0m"

	@echo "\033[0;32mMoving binaries..."
	mkdir -p bin
	mv $(BIN) bin/
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
	$(CC) -o $(NAME) -L $(MLX) $(LXFLAGS) $(B_BIN)
	@echo "\033[0m"

	@echo "\033[0;32mMoving binaries..."
	mkdir -p bin
	mv $(B_BIN) bin/
	@echo "\033[0m"

	./$(NAME)

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
	norminette $(FIL) $(B_FIL) files/$(HEADER) bonus/$(B_HEADER)
