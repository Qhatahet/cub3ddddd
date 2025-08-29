CC = cc

CFLAGS = -Werror -Wextra -Wall -IHeaders -g \
         -IMLX42/include

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX42_DIR = MLX42
MLX42_BUILD = $(MLX42_DIR)/build
MLX42_LIB = $(MLX42_BUILD)/libmlx42.a

SRCS = ./SRC/raycasting/render.c SRC/raycasting/render_utils.c SRC/raycasting/draw_walls.c \
	   SRC/raycasting/mouse.c SRC/raycasting/keyboard.c  SRC/raycasting/check.c SRC/raycasting/render_utils2.c \
	   ./SRC/mapparsing/store_colors.c ./SRC/mapparsing/validate_colors.c \
                ./SRC/mapparsing/validate_colors_utils.c ./SRC/mapparsing/store_textures.c ./SRC/mapparsing/store_textures_utils.c \
                ./SRC/mapparsing/validate_textures.c ./SRC/game_clean_up.c main.c ./SRC/mapparsing/store_map.c ./SRC/mapparsing/store_map_utils.c \
                ./SRC/mapparsing/map_validation.c ./SRC/mapparsing/element_validation.c ./SRC/mapparsing/read_file.c


OBJS_DIR := objects
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

NAME = cub3D

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX42_LIB) Headers/cub3d.h
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft \
	    $(MLX42_LIB) -ldl -lglfw -pthread -lm -o $(NAME)

$(LIBFT):
	$(MAKE) bonus -C $(LIBFT_DIR)

$(MLX42_LIB):
	@echo "Building MLX42..."
	cmake -S $(MLX42_DIR) -B $(MLX42_BUILD)
	cmake --build $(MLX42_BUILD) -j4

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)
	@rm -rf $(MLX42_BUILD)

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJS_DIR)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: fclean all clean re
