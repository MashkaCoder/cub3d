/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chasimir <chasimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:48:31 by scoach            #+#    #+#             */
/*   Updated: 2022/03/16 01:40:27 by chasimir         ###   ########.fr       */
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
	float			posX;
	float			posY;
	float			dirX;
	float			dirY;
	float			planeX;
	float			planeY;
	float			moveSpeed;
	float			rotSpeed;
	float			cameraX; // коорд х в прост кам
	float			rayDirX;
	float			rayDirY;
	float			sideDistX; //расст кот луч долж пройти от нач позиции до первой стор х
	float			sideDistY; //расст кот луч долж пройти от нач позиции до первой стор у
	float			deltaDistX; // дина луча от одной стор х до след стор х
	float			deltaDistY; // дина луча от одной стор у до след стор у
	float			perpWallDist;
	int				stepX; //в каком направлении делать шаг по оси x (либо +1, либо -1)
	int				stepY; //в каком направлении делать шаг по оси y (либо +1, либо -1)
	int				mapX; // в какой мы клеточке
	int				mapY; // в какой мы клеточке
	float			wallX; // в какое место мы ударились
	int				texX; // x-coord text
	float			step; // Насколько увеличить координату текстуры на пиксель экрана
	float			texPos; // Начальная координата текстуры
	int				texY;
	int				drawStart;
	int				drawEnd;
	int				lineHeight;
	int				side;
	int				hit;
	struct s_data	*main;
	t_pixel			*pixel;
	t_textures		*txt_pxl;
	t_keys			*keys;
	struct s_txtr	*txt;
}			t_raycast;

typedef struct s_txtr
{
	int			width;
	int			height;
	void		*north;
	void		*south;
	void		*west;
	void		*east;
	int			buffer[screenHeight][screenWidth];
}				t_txtr;

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
	// void		*mlx;
	t_textures	*north;
	t_textures	*south;
	t_textures	*west;
	t_textures	*east;
	t_txtr		*walls;
	t_raycast	*raycast;
}				t_data;

#endif
