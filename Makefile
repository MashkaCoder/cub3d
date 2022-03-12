NAME = cub3d

CUB = srcs/cub/pognali_epta.c\
	srcs/cub/init.c\

GNL = srcs/gnl/get_next_line_utils.c\
	srcs/gnl/get_next_line.c\

PARS =  srcs/parser/check_map.c\
		srcs/parser/parse_params.c\
		srcs/parser/parse_rgb.c\
		srcs/parser/texture_form.c\

UTILS = srcs/utils/utils.c\
		srcs/utils/free.c\
		srcs/utils/str_arr_utils.c\
		srcs/utils/str_arr_utils2.c\

SRC =	${GNL} ${PARS} ${UTILS} ${CUB}\
		srcs/main.c\

PATH_LIB = srcs/libft/

NAME_LIB = libft.a

LIB = srcs/libft/libft.a

HDRS = srcs/cub.h

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

# gcc -l mlx -framework OpenGL -framework AppKit cub/pognali_epta.c gnl/*.c parser/*.c libft/libft.a utils/*.c main.c
# CFLAGS = -g
# gcc -l mlx -framework OpenGL -framework AppKit cub/pognali_epta.c gnl/*.c parser/*.c libft/libft.a utils/*.c main.c && ./a.out test.cub

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
