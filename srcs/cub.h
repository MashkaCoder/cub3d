/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chasimir <chasimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 19:38:44 by chasimir          #+#    #+#             */
/*   Updated: 2022/03/17 19:38:45 by chasimir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# define S 1
# define A 0
# define D 2
# define W 13
# define ESC 53
# define AR_LEFT 123
# define AR_RIGHT 124
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64
// # include <mlx.h>
# include "../mlx/mlx.h"
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include "types.h"
# include "parser/parser.h"
# include "cub/cub_cast.h"

//Функции общего назначения (utils.c)
void	ft_error(t_data *data, char *msg, int op);
int		ft_open(char *flnm);
void	ft_gnl_read(t_data *data, int *gnl, int fd, char **ln);
void	pixel_put(t_pixel *pixel, int x, int y, int color);
// int		pixel_get(t_textures *txt, int x, int y);
int		get_pixel_color(t_textures *txt, int x, int y);
// void	pixel_put(t_raycast *raycast, int x, int y, int color);

//Функции для работы с массивом
char	**ft_arr_plus_one(char ***sub_arr, char *str, int i, int ln);
void	ft_putarr_fd(char **arr, int fd);
int		ft_arrlen(char **arr);
char	**ft_arrdup(char **arr);
char	**ft_arrjoin(char **arr1, char **arr2);

//Очистка памяти (free.c)
void	ft_context_free_err(t_data *data, char ***tmp, int aln, char *msg);
void	ft_free_data(t_data *data);
char	**ft_free_arr(char **arr, int ln);

// cub
int		dolznoBitVmain(t_data *main, t_raycast *raycast);

#endif
