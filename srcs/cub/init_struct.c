/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chasimir <chasimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:06:28 by chasimir          #+#    #+#             */
/*   Updated: 2022/03/16 19:06:29 by chasimir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	init_st_rc2(t_data *main, t_raycast *raycast)
{
	if (main->playdir == 'N')
	{
		raycast->dirX = 0;
		raycast->dirY = -1;
	}
	if (main->playdir == 'S')
	{
		raycast->dirX = 0;
		raycast->dirY = 1;
	}
	if (main->playdir == 'E')
	{
		raycast->dirX = 1;
		raycast->dirY = 0;
	}
	if (main->playdir == 'W')
	{
		raycast->dirX = -1;
		raycast->dirY = 0;
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
	raycast->posX = (float)main->player_base[0] + 0.5;
	raycast->posY = (float)main->player_base[1] + 0.5;
	raycast->main = main;
	raycast->cameraX = 0.0;
	raycast->moveSpeed = 0.09;
	raycast->rotSpeed = 0.07;
	raycast->wallX = 0;
	raycast->texX = 0;
	init_st_rc2(main, raycast);
	main->map[main->player_base[1]][main->player_base[0]] = '0';
	raycast->planeX = -raycast->dirY * 0.66;
	raycast->planeY = raycast->dirX * 0.66;
	init_key(raycast);
	init_txt(main);
}
