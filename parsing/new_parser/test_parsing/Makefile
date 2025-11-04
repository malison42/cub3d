NAME        = test_parsing

LIB_NAME    = libft.a

SRC_DIR     = /home/vzots/42_project/cub3d/parsing/new_parser
LIB_DIR     = /home/vzots/42_project/cub3d/libft
MLX_DIR     = /home/vzots/42_project/cub3d/libmlx_linux
# Добавляем VPATH, чтобы Make знал, где искать файлы *.c
VPATH       = $(SRC_DIR)

# 1. Находим все C-файлы с полным путем
ALL_C_FILES = $(wildcard $(SRC_DIR)/*.c) test.c

# 2. Преобразуем список C-файлов в список объектных файлов (.o) в текущей директории
#    $(notdir ...) удаляет путь к директории, оставляя только имя файла.
OBJ         = $(patsubst %.c,%.o,$(notdir $(ALL_C_FILES)))

HEADER      = /home/vzots/42_project/cub3d/cub.h \
			/home/vzots/42_project/cub3d/parsing/new_parser/parsing_map.h \
			/home/vzots/42_project/cub3d/libmlx_linux/mlx.h

CFLAGS      = -Wall -Wextra -Werror -I$(MLX_DIR) -I$(LIB_DIR) #-g -fsanitize=address


%.o:%.c     $(HEADER) Makefile
# Правило находит %.c в VPATH и компилирует в %.o в текущей директории
			@cp $(LIB_DIR)/libft.h libft.h
			$(CC) $(CFLAGS) $(DFLAG) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJ) $(HEADER) Makefile
			@$(MAKE) bonus -C $(LIB_DIR)
			$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -o $(NAME)

clean:
			$(MAKE) fclean -C $(LIB_DIR)
			rm -rf libft.h
			rm -rf $(OBJ)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

norm:		
			/usr/bin/norminette $(SRC) $(HEADER)

.PHONY:		all clean fclean re norm
