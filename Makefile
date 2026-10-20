NAME		= so_long

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= inc

SRCS		= main.c map_read.c map_check.c map_path.c \
			  game_init.c game_play.c cleanup.c
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
HEADER		= $(INC_DIR)/so_long.h

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

MLX_DIR		= MLX42
MLX_BUILD	= $(MLX_DIR)/build
MLX			= $(MLX_BUILD)/libmlx42.a

INCLUDES	= -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)/include

ifeq ($(shell uname -s), Darwin)
	LDFLAGS	= -L"/Users/$(USER)/.brew/opt/glfw/lib" -lglfw \
			  -framework Cocoa -framework OpenGL -framework IOKit
else
	LDFLAGS	= -ldl -lglfw -pthread -lm
endif

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) | $(MLX)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR); \
	fi
	cmake -S $(MLX_DIR) -B $(MLX_BUILD)
	cmake --build $(MLX_BUILD) -j4

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -fr $(MLX_DIR)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
