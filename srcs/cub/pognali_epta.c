/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pognali_epta.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chasimir <chasimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:04:00 by chasimir          #+#    #+#             */
/*   Updated: 2022/03/16 20:04:01 by chasimir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	calc_step_and_sidedist(t_raycast *raycast)
{
	if (raycast->rayDirX < 0)
	{
		raycast->stepX = -1;
		raycast->sideDistX = (raycast->posX - raycast->mapX)
			* raycast->deltaDistX;
	}
	else
	{
		raycast->stepX = 1;
		raycast->sideDistX = (raycast->mapX + 1.0f - raycast->posX)
			* raycast->deltaDistX;
	}
	if (raycast->rayDirY < 0)
	{
		raycast->stepY = -1;
		raycast->sideDistY = (raycast->posY - raycast->mapY)
			* raycast->deltaDistY;
	}
	else
	{
		raycast->stepY = 1;
		raycast->sideDistY = (raycast->mapY + 1.0f - raycast->posY)
			* raycast->deltaDistY;
	}
}

void	dir_and_dist(t_raycast *raycast, int x)
{
	raycast->cameraX = 2 * x / (float)screenWidth - 1;
	raycast->rayDirX = raycast->dirX + raycast->planeX * raycast->cameraX;
	raycast->rayDirY = raycast->dirY + raycast->planeY * raycast->cameraX;
	raycast->deltaDistX = fabs(1 / raycast->rayDirX);
	raycast->deltaDistY = fabs(1 / raycast->rayDirY);
	raycast->mapX = (int)raycast->posX;
	raycast->mapY = (int)raycast->posY;
}

void	search_hit(t_raycast *raycast, t_data *main)
{
	raycast->hit = 0;
	while (!raycast->hit)
	{
		if (raycast->sideDistX < raycast->sideDistY)
		{
			raycast->sideDistX += raycast->deltaDistX;
			raycast->mapX += raycast->stepX;
			raycast->side = 0;
		}
		else
		{
			raycast->sideDistY += raycast->deltaDistY;
			raycast->mapY += raycast->stepY;
			raycast->side = 1;
		}
		if (main->map[raycast->mapY][raycast->mapX] == '1')
			raycast->hit = 1;
	}
}

void	calc(t_raycast *raycast, t_data *main)
{
	int	x;

	x = 0;
	while (x < screenWidth)
	{
		dir_and_dist(raycast, x);
		calc_step_and_sidedist(raycast);
		search_hit(raycast, main);
		seach_draw_and_txt(raycast);
		choice_txt(raycast, main, x);
		x++;
	}
}

int	render(t_data *main)
{
	key_event(main->raycast, main->raycast->keys);
	calc(main->raycast, main);
	mlx_put_image_to_window(main->raycast->mlx, main->raycast->win,
		main->raycast->pixel->img, 0, 0);
	return (0);
}
