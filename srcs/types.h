/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chasimir <chasimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:48:31 by scoach            #+#    #+#             */
/*   Updated: 2022/03/08 21:01:56 by chasimir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct s_raycast
{
	void	*mlx;
	void	*win;
	float	posX;
	float	posY;
	float	dirX;
	float	dirY;
	float	planeX;
	float	planeY;
	float	moveSpeed;
	float	rotSpeed;
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
