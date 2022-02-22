#ifndef CUB_H
# define CUB_H

# define ESC 53
# define W 13
# define S 1
# define A 0
# define D 2
# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include "types.h"
# include "parser/parser.h"


//Функции общего назначения (utils.c)
void	ft_error(t_data *data, char *msg, int op);
int		ft_open(char *flnm);
void	ft_gnl_read(t_data *data, int *gnl, int fd, char **ln);
int		ft_arrlen(char **arr);

//Очистка памяти (free.c)
void	ft_free_data(t_data *data);
int		ft_free_arr(char **arr, int ln);

#endif
