# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jivan-de <jivan-de@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/29 11:23:43 by jivan-de       #+#    #+#                 #
#    Updated: 2020/03/10 10:21:33 by jivan-de      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

COM_COLOR   = \033[1;31m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m
OK_STRING    = "[OK]"
ERROR_STRING = "[ERROR]"
COM_STRING   = "Compiling"

NAME = cub3D
FLAGS = -Wall -Werror -Wextra -Ilibft -Imlx -I. -O3
SOURCES =	cub3d.c \
			config/config.c \
			config/parse.c \
			config/parse_resolution.c \
			config/parse_path.c \
			config/parse_color.c \
			config/parse_map.c \
			config/map_validate.c \
			sprites/init.c \
			sprites/read.c \
			sprites/sort.c \
			sprites/distance.c \
			sprites/render.c \
			sprites/items.c \
			utils/messages.c \
			utils/memory.c \
			utils/colors.c \
			utils/vectors.c \
			utils/spawn.c \
			utils/finalize.c \
			utils/debugger.c \
			utils/bitmap.c \
			utils/geometry.c \
			engine/run.c \
			engine/pixel.c \
			engine/line.c \
			engine/init.c \
			engine/move.c \
			engine/look.c \
			engine/hitbox.c \
			engine/textures.c \
			engine/ceilfloor.c \
			engine/ray.c \
			hud/draw.c \
			hud/hud.c \

LIBFT = libft.a
MINILIBX = libmlx.dylib
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

bonus: flag
flag: FLAGS += -DBONUS
flag: all

$(NAME): $(LIBFT) $(MINILIBX) $(OBJECTS)
	@printf "%-57b" "$(COM_COLOR)Compiling Cub3D...: $(NO_COLOR)"
	@$(CC) $(OBJECTS) $(LIBFT) -Lmlx/ -lmlx -framework OpenGL \
		-framework AppKit -o $(NAME)
	@printf "%b" "$(OK_COLOR)$(OK_STRING)\n$(NO_COLOR)"

$(LIBFT):
	@printf "%b" "$(COM_COLOR)Rolling out LibFT...\n$(NO_COLOR)"
	@$(MAKE) -C libft
	@printf "%b" "$(COM_COLOR)Moving LibFT to root...\n$(NO_COLOR)"
	@cp libft/$(LIBFT) .

$(MINILIBX):
	@printf "%b" "$(COM_COLOR)Compiling MiniLibX...\n$(NO_COLOR)"
	@$(MAKE) -C mlx > /dev/null
	@printf "%b" "$(COM_COLOR)Moving MiniLibX to root...\n$(NO_COLOR)"
	@cp mlx/$(MINILIBX) .

%.o: %.c
	@$(CC) -c $(FLAGS) $< -o $@; \
        RESULT=$$?; \
        if [ $$RESULT -ne 0 ]; then \
            printf "%-60b %b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" \
				"$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"; \
		else  \
            printf "%-60b %b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $(@F)" \
				"$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"; \
        fi; \
        exit $$RESULT

clean:
	@printf "%-57b" "$(COM_COLOR)Cleaning up binary file: $(NO_COLOR)"
	@$(RM) $(NAME)
	@printf "%b" "$(OK_COLOR)$(OK_STRING)\n$(NO_COLOR)"

fclean: clean
	@$(MAKE) -C libft fclean
	@$(MAKE) -C mlx clean > /dev/null
	@printf "%-57b" "$(COM_COLOR)Cleaning up $(NAME): $(NO_COLOR)"
	@$(RM) $(NAME) $(LIBFT) $(MINILIBX) $(OBJECTS) frame.bmp screenshot.bmp
	@printf "%b" "$(OK_COLOR)$(OK_STRING)\n$(NO_COLOR)"

re: fclean all

.PHONY: all clean fclean re flags bonus
