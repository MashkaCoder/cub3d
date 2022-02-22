NAME = cub3d


GNL = srcs/gnl/get_next_line_utils.c\
	srcs/gnl/get_next_line.c\

PARS = srcs/parser/check_mapnargs.c\
		srcs/parser/parse_map.c\
		srcs/parser/parse_params.c\

UTILS = srcs/utils/free.c\
		srcs/utils/str_arr_utils.c\
		srcs/utils/utils.c\

SRC =	${GNL} ${PARS} ${UTILS}\
		srcs/main.c\

PATH_LIB = srcs/libft/

NAME_LIB = libft.a

LIB = libft/libft.a

HDRS = srcs/cub.h

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

# CFLAGS = -g

MLX_FLAGS = -L mlx -l mlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ) $(HDRS)
		make -C mlx $(PATH_LIB)
		$(CC) $(FLAGS) $(MLX_FLAGS) -I mlx $(OBJ) -I. -o $(NAME)

bonus: $(OBJ_BONUS) $(HDRS_BONUS)
		make -C mlx
		$(CC) $(FLAGS) $(MLX_FLAGS) -I mlx $(OBJ_BONUS) -I. -o $(NAME)

clean:
		make clean -C mlx
		rm -f $(OBJ_BONUS)
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME_BONUS)
		rm -f $(NAME)

re:		fclean all

.PHONY: all clean fclean
