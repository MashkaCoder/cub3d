/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_and_search_dz.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chasimir <chasimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:04:12 by chasimir          #+#    #+#             */
/*   Updated: 2022/03/16 20:04:13 by chasimir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	draw_line(t_raycast *raycast, t_textures *txt, int y, int x)
{
	int	c;

	c = 0;
	raycast->step = (1.0f * texHeight / raycast->lineHeight);
	raycast->texPos = (float)((raycast->drawStart
				- screenHeight / 2 + raycast->lineHeight / 2) * raycast->step);
	while (c < raycast->drawStart)
	{
		pixel_put(raycast->pixel, x, c, raycast->main->ceilling);
		c++;
	}
	while (y <= raycast->drawEnd)
	{
		raycast->texY = (int)raycast->texPos & (texHeight - 1);
		raycast->texPos += raycast->step;
		pixel_put(raycast->pixel, x, y,
			get_pixel_color(txt, texWidth - raycast->texX - 1, raycast->texY));
		y++;
	}
	while (raycast->drawEnd < screenHeight)
	{
		pixel_put(raycast->pixel, x, raycast->drawEnd, raycast->main->floor);
		raycast->drawEnd++;
	}
}

void	seach_draw_and_txt(t_raycast *raycast)
{
	if (!raycast->side)
	{
		raycast->perpWallDist = raycast->sideDistX - raycast->deltaDistX;
		raycast->wallX = raycast->posY
			+ raycast->perpWallDist * raycast->rayDirY;
	}
	else
	{
		raycast->perpWallDist = raycast->sideDistY - raycast->deltaDistY;
		raycast->wallX = raycast->posX
			+ raycast->perpWallDist * raycast->rayDirX;
	}
	raycast->wallX -= floorf(raycast->wallX);
	raycast->texX = (int)(raycast->wallX * (float)texWidth);
	if (!raycast->side && raycast->rayDirX > 0)
		raycast->texX = texWidth - raycast->texX - 1;
	if (raycast->side && raycast->rayDirY < 0)
		raycast->texX = texWidth - raycast->texX - 1;
	raycast->lineHeight = (int)(screenHeight / raycast->perpWallDist);
	raycast->drawStart = -raycast->lineHeight / 2 + screenHeight / 2;
	if (raycast->drawStart < 0)
		raycast->drawStart = 0;
	raycast->drawEnd = raycast->lineHeight / 2 + screenHeight / 2;
	if (raycast->drawEnd >= screenHeight)
		raycast->drawEnd = screenHeight - 1;
}

void	choice_txt(t_raycast *raycast, t_data *main, int x)
{
	t_textures	*txt;

	if (!raycast->side && raycast->mapX < raycast->posX)
		txt = main->west;
	if (!raycast->side && raycast->mapX >= raycast->posX)
		txt = main->east;
	if (raycast->side && raycast->mapY < raycast->posY)
		txt = main->north;
	if (raycast->side && raycast->mapY >= raycast->posY)
		txt = main->south;
	draw_line(raycast, txt, raycast->drawStart, x);
}
