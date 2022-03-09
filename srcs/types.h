/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chasimir <chasimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:48:31 by scoach            #+#    #+#             */
/*   Updated: 2022/03/09 20:04:11 by chasimir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

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
	// struct s_data	*main;
}			t_raycast;

typedef struct s_txtr
{
	int		width;
	int		height;
	void	*north;
	void	*south;
	void	*west;
	void	*east;
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
	t_txtr		*walls;
	t_raycast	*raycast;
}				t_data;

#endif
