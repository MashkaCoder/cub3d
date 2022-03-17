/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chasimir <chasimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:48:31 by scoach            #+#    #+#             */
/*   Updated: 2022/03/17 19:37:43 by chasimir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct s_pixel
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
}				t_pixel;

typedef struct s_textures
{
	void	*img_data;
	char	*img_ptr;
	int		*data;
	int		line_len;
	int		endian;
	int		width;
	int		height;
	int		bpp;
}	t_textures;

typedef struct s_keys
{
	int	key_a;
	int	key_d;
	int	key_w;
	int	key_s;
	int	key_la;
	int	key_ra;
}			t_keys;

typedef struct s_raycast
{
	void			*mlx;
	void			*win;
	float			pos_x;
	float			pos_y;
	float			dir_x;
	float			dir_y;
	float			plane_x;
	float			plane_y;
	float			move_speed;
	float			rot_speed;
	float			camera_x; // коорд х в прост кам
	float			raydir_x;
	float			raydir_y;
	float			side_dist_x; //расст кот луч долж пройти от нач позиции до первой стор х
	float			side_dist_y; //расст кот луч долж пройти от нач позиции до первой стор у
	float			delta_dist_x; // дина луча от одной стор х до след стор х
	float			delta_dist_y; // дина луча от одной стор у до след стор у
	float			perp_wall_dist;
	int				step_x; //в каком направлении делать шаг по оси x (либо +1, либо -1)
	int				step_y; //в каком направлении делать шаг по оси y (либо +1, либо -1)
	int				map_x; // в какой мы клеточке
	int				map_y; // в какой мы клеточке
	float			wall_x; // в какое место мы ударились
	int				tex_x; // x-coord text
	float			step; // Насколько увеличить координату текстуры на пиксель экрана
	float			tex_pos; // Начальная координата текстуры
	int				tex_y;
	int				draw_start;
	int				draw_end;
	int				line_height;
	int				side;
	int				hit;
	struct s_data	*main;
	t_pixel			*pixel;
	t_textures		*txt_pxl;
	t_keys			*keys;
	struct s_txtr	*txt;
}			t_raycast;

// typedef struct s_txtr
// {
// 	int			width;
// 	int			height;
// 	void		*north;
// 	void		*south;
// 	void		*west;
// 	void		*east;
// 	int			buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
// }				t_txtr;

typedef struct s_data
{
	int			width;
	int			high;
	char		**map;
	char		*nswe[4];
	int			floor;
	int			ceilling;
	int			player_base[2];
	char		playdir;
	char		**gnln;
	t_textures	*north;
	t_textures	*south;
	t_textures	*west;
	t_textures	*east;
	t_raycast	*raycast;
}				t_data;

#endif
