/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chasimir <chasimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:06:28 by chasimir          #+#    #+#             */
/*   Updated: 2022/03/17 19:41:04 by chasimir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	init_st_rc2(t_data *main, t_raycast *raycast)
{
	if (main->playdir == 'N')
	{
		raycast->dir_x = 0;
		raycast->dir_y = -1;
	}
	if (main->playdir == 'S')
	{
		raycast->dir_x = 0;
		raycast->dir_y = 1;
	}
	if (main->playdir == 'E')
	{
		raycast->dir_x = 1;
		raycast->dir_y = 0;
	}
	if (main->playdir == 'W')
	{
		raycast->dir_x = -1;
		raycast->dir_y = 0;
	}
}

void	init_key(t_raycast *raycast)
{
	t_keys	*keys;

	keys = malloc(sizeof(t_keys));
	ft_memset(keys, 0, sizeof(t_keys));
	raycast->keys = keys;
}

void	init_st_rc(t_data *main, t_raycast *raycast)
{
	raycast->pos_x = (float)main->player_base[0] + 0.5;
	raycast->pos_y = (float)main->player_base[1] + 0.5;
	raycast->main = main;
	raycast->camera_x = 0.0;
	raycast->move_speed = 0.09;
	raycast->rot_speed = 0.07;
	raycast->wall_x = 0;
	raycast->tex_x = 0;
	init_st_rc2(main, raycast);
	main->map[main->player_base[1]][main->player_base[0]] = '0';
	raycast->plane_x = -raycast->dir_y * 0.66;
	raycast->plane_y = raycast->dir_x * 0.66;
	init_key(raycast);
	init_txt(main);
}
