CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

NAME = cub3d

NAME_B = cub3d_bonus

SRC = _mandatory/main.c \
	_mandatory/game_event.c \
	_mandatory/parse/parse.c \
	_mandatory/parse/parse_utils.c \
	_mandatory/parse/parse_utils2.c \
	_mandatory/parse/parse_map.c \
	_mandatory/parse/check_textures.c \
	_mandatory/utils/init.c \
	_mandatory/utils/free.c \
	_mandatory/utils/free_utils.c \
	_mandatory/utils/utils.c \
	_mandatory/utils/convert_map.c \
	_mandatory/exec/draw.c \
	_mandatory/exec/draw_background.c \
	_mandatory/exec/draw_utils.c \
	_mandatory/exec/exec_utils.c \
	_mandatory/exec/move.c \
	_mandatory/exec/move_rotate.c \
	_mandatory/exec/raycasting.c \
	_mandatory/exec/raycasting_init.c \

SRC_B = _bonus/main_bonus.c \
		_bonus/game_event_bonus.c \
		_bonus/parse_bonus/parse.c \
		_bonus/parse_bonus/parse_utils.c \
		_bonus/parse_bonus/parse_utils2.c \
		_bonus/parse_bonus/parse_map.c \
		_bonus/parse_bonus/check_textures.c \
		_bonus/parse_bonus/check_sprites.c \
		_bonus/utils_bonus/init.c \
		_bonus/utils_bonus/init_elements.c \
		_bonus/utils_bonus/free.c \
		_bonus/utils_bonus/free_utils.c \
		_bonus/utils_bonus/utils.c \
		_bonus/utils_bonus/convert_map.c \
		_bonus/exec_bonus/draw.c \
		_bonus/exec_bonus/draw_background.c \
		_bonus/exec_bonus/draw_utils.c \
		_bonus/exec_bonus/mini_map.c \
		_bonus/exec_bonus/exec_utils.c \
		_bonus/exec_bonus/move.c \
		_bonus/exec_bonus/move_rotate.c \
		_bonus/exec_bonus/raycasting.c \
		_bonus/exec_bonus/raycasting_init.c \
		_bonus/exec_bonus/sprites.c \

HEADER = cub.h

HEADER_B = cub_bonus.h

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

re_bonus: fclean bonus

.PHONY: all clean fclean re re_bonus
