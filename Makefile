NAME		= cub3D

MLX_NAME	= libmlx.a
LIB_NAME	= libft.a

SRC			= main.c

OBJ			= $(SRC:.c=.o)

HEADER		= cub.h keys_macos.h keys_linux.h

CFLAGS		= -Wall -Wextra -Werror #-g -fsanitize=address
LIB_DIR		= libft

ifeq ($(shell uname), Darwin)
	MLX_DIR	= libmlx_macos
	LFLAGS	= -L$(MLX_DIR) -lmlx -lm -framework OpenGL -framework AppKit -L$(LIB_DIR) -lft
	DFLAG	= -DDARWIN
else
	MLX_DIR	= libmlx_linux
	LFLAGS	= -L$(MLX_DIR) -lmlx -lm -lft -lXext -lX11 -L$(LIB_DIR) -lft
endif

%.o:%.c		$(HEADER) Makefile
			@cp $(LIB_DIR)/libft.h libft.h
			@cp $(MLX_DIR)/mlx.h mlx.h
			$(CC) $(CFLAGS) $(DFLAG) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJ) $(HEADER) Makefile
			@$(MAKE) -C $(LIB_DIR)
			@$(MAKE) -C $(MLX_DIR)
			$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -o $(NAME)

clean:
			$(MAKE) fclean -C $(LIB_DIR)
			$(MAKE) clean -C $(MLX_DIR)
			rm -rf libft.h
			rm -rf mlx.h
			rm -rf $(OBJ)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
