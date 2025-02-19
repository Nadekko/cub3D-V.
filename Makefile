CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

NAME = cub3d

NAME_B = cub3d_bonus

SRC = main.c \
	main_utils.c \
	parse/parse.c \
	parse/parse_utils.c \
	parse/parse_utils2.c \
	parse/parse_map.c \
	parse/check_textures.c \
	utils/init.c \
	utils/free.c \
	utils/free_utils.c \
	utils/utils.c \
	utils/convert_map.c \
	exec/draw.c \
	exec/draw_background.c \
	exec/draw_utils.c \
	exec/exec_utils.c \
	exec/move.c \
	exec/move_rotate.c \
	exec/move_utils.c \
	exec/raycasting.c \
	exec/raycasting_init.c \

SRC_B = bonus/main_bonus.c \
	main_utils.c \
	parse/parse.c \
	parse/parse_utils.c \
	parse/parse_utils2.c \
	parse/parse_map.c \
	parse/check_textures.c \
	utils/init.c \
	utils/free.c \
	utils/free_utils.c \
	utils/utils.c \
	utils/convert_map.c \
	exec/draw.c \
	exec/draw_background.c \
	exec/draw_utils.c \
	exec/exec_utils.c \
	exec/move.c \
	bonus/move_rotate_bonus.c \
	bonus/move_utils_bonus.c \
	exec/raycasting.c \
	exec/raycasting_init.c \

HEADER = cub.h

HEADER_B = bonus/cub_bonus.h

LIBFT = libft/libft.a

MiniLibX = minilibx-linux

MiniLibX_exec = minilibx-linux/libmlx.a

OBJ = $(SRC:.c=.o)

OBJ_B = $(SRC_B:.c=.o)

GREEN = \033[0;32m
BLUE = \033[0;34m
CYAN = \033[0;36m
YELLOW = \033[0;33m
PURPLE = \033[0;35m
NC = \033[0m

all: $(MiniLibX_exec) $(LIBFT) $(NAME)

$(NAME): $(OBJ) $(HEADER) $(LIBFT) $(MiniLibX_exec)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MiniLibX_exec) -lXext -lX11 -lm
	@echo "$(GREEN)		*----------------------------------*\n \
			|   	[OK] $(NAME) created   	   |\n \
			*----------------------------------*$(NC)"

bonus: $(MiniLibX_exec) $(OBJ_B) $(HEADER_B) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME_B) $(OBJ_B) $(LIBFT) $(MiniLibX_exec) -lXext -lX11 -lm
	@echo "$(GREEN)		*----------------------------------*\n \
			|   	[OK] $(NAME_B) created   	   |\n \
			*----------------------------------*$(NC)"

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(LIBFT):
	@make -C libft
	@echo "$(BLUE)		*----------------------------------*\n \
			|        [OK] LIBFT created        |\n \
			*----------------------------------*$(NC)"

$(MiniLibX):
	@git clone https://github.com/42Paris/minilibx-linux.git $@

$(MiniLibX_exec): $(MiniLibX)
	@make -s -C minilibx-linux
	@echo "$(CYAN)			*----------------------------------*\n \
				|        [OK] MiniLibX created     |\n \
				*----------------------------------*$(NC)"

clean:
	@make clean -C libft
	@echo "$(YELLOW)[OK]$(NC) libft clean completed"
	rm -f $(OBJ) $(OBJ_B)
	@echo "$(PURPLE)[OK]$(NC) cub3d clean completed"

fclean: clean
	@rm -rf $(MiniLibX)
	@make fclean -C libft
	@echo "$(YELLOW)[OK]$(NC) libft fclean completed"
	rm -f $(NAME) $(NAME_B)
	@echo "$(PURPLE)[OK]$(NC) cub3d fclean completed"

re: fclean all

.PHONY: all clean fclean re
