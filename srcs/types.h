/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoach <scoach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:48:31 by scoach            #+#    #+#             */
/*   Updated: 2022/03/08 19:19:15 by scoach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

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
	int		width;
	int		high;
	char	**map;
	char	*nswe[4];
	int		floor[3];
	int		ceilling[3];
	int		player_base[2];
	char	playdir;
	char	**gnln;
	void	*mlx;
	t_txtr	*walls;
}				t_data;

#endif