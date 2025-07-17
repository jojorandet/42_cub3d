GREEN = \033[0;32m
RESET = \033[0m

NAME			=			cub3d
CC				=			cc

UNAME			=			$(shell uname)

DIR_BUILD		=			./build
DIR_INCLUDE		=			./include

MLX_PATH_UNIX	:=			./libs/minilibx-linux/
MLX_NAME_UNIX	:=			libmlx.a
MLX_PATH_OSX	:=			./libs/minilibx-macos
MLX_NAME_OSX	:=			libmlx.a

LIBFT_PATH		:=			./libs/libft/
LIBFT_NAME		:=			libft.a
LIBFT			:=			$(LIBFT_PATH)$(LIBFT_NAME)

ifeq ($(UNAME), Darwin)
	MLX_PATH	= $(MLX_PATH_OSX)
	MLX_NAME	= $(MLX_NAME_OSX)
	LIBRARIES	= -fsanitize=address -lft -Lmlx -lmlx -framework OpenGL -framework AppKit
else ifeq ($(UNAME), Linux)
	MLX_PATH	= $(MLX_PATH_UNIX)
	MLX_NAME	= $(MLX_NAME_UNIX)
	LIBRARIES	= -lft -lmlx -lX11 -lXext -lm -lz
endif

MLX = $(MLX_PATH)$(MLX_NAME)

#------------ SOURCES ------------#

DIR_MAIN		=			./src/main
SRC_MAIN		=			main.c \
							exit_cub3d.c \
							error_handling.c \
							free_utils.c
MAIN			=			$(addprefix $(DIR_MAIN)/, $(SRC_MAIN))

DIR_PARSING		=			./src/parsing
SRC_PARSING		=			flood_fill.c \
							map_desription.c \
							main_parsing.c \
							check_file.c \
							init_player.c \
							extract_texture.c \
							extract_colour.c \
							validate_colour.c \
							get_file_content.c \
							parse_texture_and_colour.c
#init_data.c
PARSING			=			$(addprefix $(DIR_PARSING)/, $(SRC_PARSING))

DIR_UTILS		=			./src/utils
SRC_UTILS		=			vector.c \
							get_next_line.c \
							get_next_line_utils.c \
							string_array_len.c \
							dda_algorithm.c
UTILS			=			$(addprefix $(DIR_UTILS)/, $(SRC_UTILS))

DIR_DEBUG		=			./src/debug
SRC_DEBUG		=			debug.c \
							print_grid.c
DEBUG 			=			$(addprefix $(DIR_DEBUG)/, $(SRC_DEBUG))

DIR_EVENTS		=			./src/events
SRC_EVENTS		=			keyboard_events.c
EVENTS			=			$(addprefix $(DIR_EVENTS)/, $(SRC_EVENTS))

DIR_RENDER_IMG	=			./src/render_img
SRC_RENDER_IMG	=			init_img.c \
							render.c \
							player_movement.c \
							valid_next_movement.c
RENDER_IMG		=			$(addprefix $(DIR_RENDER_IMG)/, $(SRC_RENDER_IMG))

DIR_MINIMAP		=			./src/minimap
SRC_MINIMAP		=			draw_player.c \
							minimap.c \
							print_minimap.c \
							minifov.c \
							mini_dda.c
MINIMAP 		=			$(addprefix $(DIR_DEBUG)/, $(SRC_MINIMAP))

DIR_BONUS		=			./src/bonus
SRC_BONUS		=			init_bonus.c \
							fps_counter.c
BONUS			=			$(addprefix $(DIR_BONUS)/, $(SRC_BONUS))

DIR_RAYCASTING		=		./src/raycasting
SRC_RAYCASTING		=		game_loop.c \
							draw_walls.c 

RAYCASTING 		=			$(addprefix $(DIR_RAYCASTING)/, $(SRC_RAYCASTING))


SOURCES			=			$(MAIN) $(PARSING) $(UTILS) $(DEBUG) $(EVENTS) $(RENDER_IMG) $(MINIMAP) $(RAYCASTING) $(BONUS)
vpath %.c		 			$(DIR_MAIN) $(DIR_PARSING) $(DIR_UTILS) $(DIR_DEBUG) $(DIR_EVENTS) $(DIR_IMG) $(DIR_RENDER_IMG) $(DIR_MINIMAP) $(DIR_RAYCASTING) $(DIR_BONUS)

OBJECTS			:= 			$(addprefix $(DIR_BUILD)/, $(notdir $(SOURCES:.c=.o)))
DEPS			:=			$(OBJECTS:.o=.d)

CFLAGS			=			-Wall -Werror -Wextra $(INC_FLAGS) -g -MMD -MP -O3
INC_FLAGS		:=			-I $(DIR_INCLUDE) -I $(LIBFT_PATH) -I $(MLX_PATH)
LIBRARY_PATHS	:=			-L$(LIBFT_PATH) -L$(MLX_PATH)

#------------- RULES -------------#

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBRARY_PATHS) $(LIBRARIES) -o $@
	@echo "$(GREEN)Cube3d: Make successful, can execute ./cub3d$(RESET)"

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(MLX):
	@make -C $(MLX_PATH) 2> /dev/null

$(DIR_BUILD)/%.o: %.c | $(DIR_BUILD)
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

$(DIR_BUILD):
	@mkdir -p $@

clean:
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(MLX_PATH) 2>/dev/null || true
	@rm -rf $(DIR_BUILD)
	@rm -f libmlx.dylib

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)
	@echo "$(GREEN)Cube3d: fclean complete.$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus

.SILENT:

-include $(DEPS)