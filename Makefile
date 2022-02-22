NAME = cub3d


GNL = srcs/gnl/get_next_line_utils.c\
	srcs/gnl/get_next_line.c\

# PARS =  srcs/parser/parse_map.c\
# 		srcs/parser/check_mapnargs.c\
# 		srcs/parser/parse_params.c\

# UTILS = srcs/utils/utils.c\
# 		srcs/utils/free.c\
# 		srcs/utils/str_arr_utils.c\

SRC =	${GNL} ${PARS} ${UTILS}\
		srcs/main.c\

PATH_LIB = srcs/libft/

NAME_LIB = libft.a

LIB = srcs/libft/libft.a

HDRS = srcs/cub.h

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

# CFLAGS = -g

MLX_FLAGS = -L mlx -l mlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ) $(HDRS)
		make -C mlx
		make -C $(PATH_LIB)
		$(CC) $(FLAGS) $(MLX_FLAGS) -I mlx $(OBJ) $(LIB) -I. -o $(NAME)

clean:
		make clean -C $(PATH_LIB)
		make clean -C mlx
		rm -f $(OBJ_BONUS)
		rm -f $(OBJ)

fclean: clean
		make fclean -C $(PATH_LIB)
		rm -f $(NAME_BONUS)
		rm -f $(NAME)

re:		fclean all

reclean: re
	$(RM) $(OBJ)
	make clean -C $(PATH_LIB)

.PHONY: all clean fclean
