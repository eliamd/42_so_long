# =============================== VARIABLES =================================== #

NAME			= so_long
CC				= cc
CFLAGS			= -Wall -Wextra -Werror $(GLFW_INC)
MLX42_PATH		= minilibx
LIBFT_PATH		= 42_libft-mylibft
MLX42			= $(MLX42_PATH)/build/libmlx42.a
LIBFT			= $(LIBFT_PATH)/libft.a
RM				= rm -f
CLONE 			= git clone --depth=1

# ================================ COULEURS =================================== #

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
NC = \033[0m # No Color

# =============================== DETECTION OS =============================== #

UNAME := $(shell uname)
ARCH := $(shell uname -m)

# Configuration pour MacOS
ifeq ($(UNAME), Darwin)
	ifeq ($(ARCH), arm64)
		GLFW_FLAGS = -lglfw -L"/opt/homebrew/lib/"
		GLFW_INC = -I"/opt/homebrew/include"
		OS_MSG = "MacOS ARM"
	else
		GLFW_FLAGS = -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
		GLFW_INC = -I"/Users/$(USER)/.brew/opt/glfw/include"
		OS_MSG = "MacOS Intel"
	endif
	FRAMEWORK = -framework Cocoa -framework OpenGL -framework IOKit
else
	GLFW_FLAGS = -ldl -lglfw -pthread -lm
	GLFW_INC =
	FRAMEWORK =
	OS_MSG = "Linux"
endif

# =============================== SOURCES ===================================== #

SRCS = 	src/main.c \
		src/map/map_malloc.c \
		src/map/map_check.c \
		src/map/map_parse.c \
		src/map/map_flood_fill.c \
		src/init/init_game.c \
		src/init/init_textures.c \
		src/utils/cleanup.c \
		src/utils/input.c \
		src/utils/player.c \
		src/utils/render.c \

OBJS = $(SRCS:.c=.o)

# ============================= PROGRESS BAR ================================= #

TOTAL_FILES := $(words $(SRCS))
CURRENT_FILE := 0
PROGRESS_WIDTH := 40

define update_progress
	$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
	$(eval PERCENTAGE=$(shell echo $$(($(CURRENT_FILE) * 100 / $(TOTAL_FILES)))))
	$(eval PROGRESS=$(shell echo $$(($(CURRENT_FILE) * $(PROGRESS_WIDTH) / $(TOTAL_FILES)))))
	printf "\r$(BLUE)[%3d%%] $(GREEN)Building %-50s$(NC)" $(PERCENTAGE) "$1"
endef

# ============================== REGLES PRINCIPALES ========================== #

all:			$(LIBFT) $(MLX42) $(NAME)

# Compilation de la libft
$(LIBFT):
			@printf "$(BLUE)[  0%%] $(GREEN)Building libft...$(NC)\n"
			@make -C $(LIBFT_PATH)
			@printf "$(BLUE)[100%%] $(GREEN)Libft built successfully$(NC)\n"

# Compilation de MLX42
$(MLX42):
			@printf "$(BLUE)[  0%%] $(GREEN)Building MLX42...$(NC)\n"
			@cmake $(MLX42_PATH) -B $(MLX42_PATH)/build
			@make -C $(MLX42_PATH)/build -j4
			@printf "$(BLUE)[100%%] $(GREEN)MLX42 built successfully$(NC)\n"

$(NAME): $(OBJS)
			$(CC) $(OBJS) $(MLX42) -L$(LIBFT_PATH) -lft $(GLFW_FLAGS) $(FRAMEWORK) -o $(NAME)
			@printf "$(BLUE)[100%%] $(GREEN)$(NAME) is compiled !! $(NC)\n"
			@echo $(HEADER)

%.o: %.c
			@$(call update_progress,$<)
			@$(CC) $(CFLAGS) -I$(MLX42_PATH)/include -I$(LIBFT_PATH) -c $< -o $@
			@printf "\n"

# ================================== CLEAN ==================================== #

clean:
			@echo "$(YELLOW)Cleaning object files...$(NC)"
			@make -C $(LIBFT_PATH) clean
			@rm -rf $(MLX42_PATH)/build
			@rm -f $(OBJS)
			@echo "$(GREEN)Object files cleaned!$(NC)"

fclean:		clean
			@echo "$(YELLOW)Cleaning all files...$(NC)"
			@make -C $(LIBFT_PATH) fclean
			@rm -f $(NAME)
			@echo "$(GREEN)All files cleaned!$(NC)"

# ================================= REBUILD =================================== #

re:			fclean all
			@echo "$(GREEN)>>> Cleaned and rebuilt everything! <<<$(DEF_COLOR)"

# ================================ PHONY ====================================== #

.PHONY:		all clean fclean re
