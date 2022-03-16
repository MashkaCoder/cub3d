/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chasimir <chasimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 03:41:10 by chasimir          #+#    #+#             */
/*   Updated: 2022/03/16 03:46:59 by chasimir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	rotate_l(t_raycast *raycast)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = raycast->dirX;
	old_plane_x = raycast->planeX;
	raycast->dirX = raycast->dirX * cos(-raycast->rotSpeed)
		- raycast->dirY * sin(-raycast->rotSpeed);
	raycast->dirY = old_dir_x * sin(-raycast->rotSpeed)
		+ raycast->dirY * cos(-raycast->rotSpeed);
	raycast->planeX = raycast->planeX * cos(-raycast->rotSpeed)
		- raycast->planeY * sin(-raycast->rotSpeed);
	raycast->planeY = old_plane_x * sin(-raycast->rotSpeed)
		+ raycast->planeY * cos(raycast->rotSpeed);
}

void	rotate_r(t_raycast *raycast)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = raycast->dirX;
	old_plane_x = raycast->planeX;
	raycast->dirX = raycast->dirX * cos(raycast->rotSpeed)
		- raycast->dirY * sin(raycast->rotSpeed);
	raycast->dirY = old_dir_x * sin(raycast->rotSpeed)
		+ raycast->dirY * cos(raycast->rotSpeed);
	raycast->planeX = raycast->planeX * cos(raycast->rotSpeed)
		- raycast->planeY * sin(raycast->rotSpeed);
	raycast->planeY = old_plane_x * sin(raycast->rotSpeed)
		+ raycast->planeY * cos(raycast->rotSpeed);
}
