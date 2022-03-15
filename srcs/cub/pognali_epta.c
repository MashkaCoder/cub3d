#include "../cub.h"

int	free_all(void)
{
	exit(EXIT_SUCCESS);
}

int ft_sign(double num)
{
 if (num < 0)
  return (-1);
 return (1);
}

void strafe(t_raycast *raycast, int dir)
{
 double new_pos_y;
 double new_pos_x;

 new_pos_y = raycast->posY + raycast->dirX * raycast->moveSpeed * dir;
 new_pos_x = raycast->posX + raycast->dirY * raycast->moveSpeed * -dir;
 if ((raycast->main->map[(int)(new_pos_y + 0.1 * ft_sign(new_pos_y - raycast->posY))][(int)raycast->posX] ) == '0')
  	raycast->posY = new_pos_y;
 if ((raycast->main->map[(int)raycast->posY][(int)(new_pos_x + 0.1 * ft_sign(new_pos_x - raycast->posX))] ) == '0')
  	raycast->posX = new_pos_x;
}
int	keyhook(int keycode, t_raycast *raycast)
{
	float	oldDirX;
	float	oldPlaneX;

	oldDirX = raycast->dirX;
	oldPlaneX = raycast->planeX;
	if (keycode == ESC)
		free_all();
	if (keycode == AR_LEFT)
	{
		raycast->dirX = raycast->dirX * cos(-raycast->rotSpeed) - raycast->dirY * sin(-raycast->rotSpeed);
		raycast->dirY = oldDirX * sin(-raycast->rotSpeed) + raycast->dirY * cos(-raycast->rotSpeed);
		raycast->planeX = raycast->planeX * cos(-raycast->rotSpeed) - raycast->planeY * sin(-raycast->rotSpeed);
		raycast->planeY = oldPlaneX * sin(-raycast->rotSpeed) + raycast->planeY * cos(raycast->rotSpeed);
	}
	if (keycode == AR_RIGHT)
	{
		raycast->dirX = raycast->dirX * cos(raycast->rotSpeed) - raycast->dirY * sin(raycast->rotSpeed);
		raycast->dirY = oldDirX * sin(raycast->rotSpeed) + raycast->dirY * cos(raycast->rotSpeed);
		raycast->planeX = raycast->planeX * cos(raycast->rotSpeed) - raycast->planeY * sin(raycast->rotSpeed);
		raycast->planeY = oldPlaneX * sin(raycast->rotSpeed) + raycast->planeY * cos(raycast->rotSpeed);
	}
	if (keycode == S)
	{
		if(raycast->main->map[(int)raycast->posY][(int)(raycast->posX - raycast->dirX * (float)0.11)] != '1')
			raycast->posX -= raycast->dirX * raycast->moveSpeed;
		if(raycast->main->map[(int)(raycast->posY - raycast->dirY * (float)0.11)][(int)raycast->posX] != '1')
			raycast->posY -= raycast->dirY * raycast->moveSpeed;
	}
	if (keycode == A)
	{
		// if(raycast->main->map[(int)raycast->posY][(int)(raycast->posX - raycast->planeX * (float)0.11)] != '1')
		// 	raycast->posX -= raycast->posX + raycast->dirX * raycast->moveSpeed * 1;
		// 	// raycast->posX -= raycast->planeX * raycast->moveSpeed;
		// if(raycast->main->map[(int)(raycast->posY - raycast->planeY * (float)0.11)][(int)raycast->posX] != '1')
		// 	raycast->posY -= raycast->posY + raycast->dirY * raycast->moveSpeed * -1;
		// 	// raycast->posY -= raycast->planeY * raycast->moveSpeed;
		strafe(raycast, -1);
	}
	if (keycode == D)
	{
		// if(raycast->main->map[(int)raycast->posY][(int)(raycast->posX + raycast->planeX * (float)0.11)] != '1')
		// 	// raycast->posX += raycast->planeX * raycast->moveSpeed;
		// 	raycast->posX -= raycast->posX + raycast->dirX * raycast->moveSpeed * -1;
		// if(raycast->main->map[(int)(raycast->posY + raycast->planeY * (float)0.11)][(int)(raycast->posX)] != '1')
		// 	// raycast->posY += raycast->planeY * raycast->moveSpeed;
		// 	raycast->posY -= raycast->posY + raycast->dirY * raycast->moveSpeed * 1;
		strafe(raycast, 1);

	}
	if (keycode == W)
	{
		if(raycast->main->map[(int)raycast->posY][(int)(raycast->posX + raycast->dirX * (float)0.11)] != '1')
			raycast->posX += raycast->dirX * raycast->moveSpeed;
		if(raycast->main->map[(int)(raycast->posY + raycast->dirY * (float)0.11)][(int)raycast->posX] != '1')
			raycast->posY += raycast->dirY * raycast->moveSpeed;
	}
	return (0);
}

void	calc_step_and_sideDist(t_raycast *raycast)
{
	if (raycast->rayDirX < 0)
	{
		raycast->stepX = -1;
		raycast->sideDistX = (raycast->posX - raycast->mapX) * raycast->deltaDistX;
	}
	else
	{
		raycast->stepX = 1;
		raycast->sideDistX = (raycast->mapX + 1.0 - raycast->posX) * raycast->deltaDistX;
		// raycast->sideDistX = (raycast->posX + 1.0) * raycast->deltaDistX;
	}
	if (raycast->rayDirY < 0)
	{
		raycast->stepY = -1;
		raycast->sideDistY = (raycast->posY - raycast->mapY) * raycast->deltaDistY;
	}
	else
	{
		raycast->stepY = 1;
		raycast->sideDistY = (raycast->mapY + 1.0 - raycast->posY) * raycast->deltaDistY;
		// raycast->sideDistY = (raycast->posY + 1.0) * raycast->deltaDistY;
	}
}

void draw_line(int x, int drawStart, int drawEnd, int color, t_raycast *raycast)
{
	int	c;

	c = 0;
	(void)color;
	// if (color)
	// 	mlx_pixel_put(raycast->mlx, raycast->win, x, drawStart, color);
	while (c < drawStart && color == 0)
	{
		// pixel_put(raycast->pixel, x, c, raycast->main->ceilling);
		// pixel_put(raycast, x, c, raycast->main->ceilling);
		mlx_pixel_put(raycast->mlx, raycast->win, x, c, raycast->main->ceilling);
		c++;
	}
	// while (drawStart <= drawEnd)
	// {
	// 	// pixel_put(raycast->pixel, x, drawStart, color);
	// 	// pixel_put(raycast, x, drawStart, color);
	// 	drawStart++;
	// }
	while (drawEnd < screenHeight && color == 0)
	{
		// pixel_put(raycast, x, drawEnd, raycast->main->floor);
		drawEnd++;
		// pixel_put(raycast->pixel, x, drawEnd, raycast->main->floor);
		mlx_pixel_put(raycast->mlx, raycast->win, x, drawEnd, raycast->main->floor);
	}
}

void	dir_and_dist(t_raycast *raycast, t_data *main, int x)
{
	(void)main;
	raycast->cameraX = 2 * x / (float)screenWidth - 1;
	raycast->rayDirX = raycast->dirX + raycast->planeX * raycast->cameraX;
	raycast->rayDirY = raycast->dirY + raycast->planeY * raycast->cameraX;
	raycast->deltaDistX = fabs(1 / raycast->rayDirX);
	raycast->deltaDistY = fabs(1 / raycast->rayDirY);
	raycast->mapX = (int)raycast->posX;
	raycast->mapY = (int)raycast->posY;
}

void	calc(t_raycast *raycast, t_data *main)
{
	int	x;
	int	hit;
	int	side;
	int	lineHeight;
	int	drawStart;
	int	drawEnd;

	x = 0;
	while (x < screenWidth)
	{
		hit = 0;
		dir_and_dist(raycast, main, x);
		calc_step_and_sideDist(raycast);
		while (!hit)
		{
			if (raycast->sideDistX < raycast->sideDistY)
			{
				raycast->sideDistX += raycast->deltaDistX;
				raycast->mapX += raycast->stepX;
				side = 0;
			}
			else
			{
				raycast->sideDistY += raycast->deltaDistY;
				raycast->mapY += raycast->stepY;
				side = 1;
			}
			if (main->map[raycast->mapY][raycast->mapX] == '1') ///////////x y
				hit = 1;
		}
		if (!side)
		{
			raycast->perpWallDist = raycast->sideDistX - raycast->deltaDistX;
			// raycast->wallX = raycast->posX + raycast->perpWallDist * raycast->rayDirX;
		}
		else
		{
			raycast->perpWallDist = raycast->sideDistY - raycast->deltaDistY;
			// raycast->wallX = raycast->posY + raycast->sideDistX * raycast->rayDirY;
		}
		// raycast->wallX -= floorf(raycast->wallX);
		// raycast->texX = (int)(raycast->wallX * (float)texWidth);
		// if (!side && raycast->rayDirX > 0)
		// 	raycast->texX = texWidth - raycast->texX - 1;
		// if (side && raycast->rayDirX < 0)
		// 	raycast->texX = texWidth - raycast->texX - 1;
		lineHeight = (int)(screenHeight / raycast->perpWallDist);
		drawStart = -lineHeight / 2 + screenHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;
		int	color;
		t_textures *txt;
		if (!side && raycast->mapX < main->player_base[0]) // w
			txt = main->west;
		if (!side && raycast->mapX >= main->player_base[0]) // e
			txt = main->east;
		if (side && raycast->mapY < main->player_base[1]) // n
			txt = main->north;
		if (side && raycast->mapY >= main->player_base[1]) // s
			txt = main->south;
		// if (!side && raycast->mapX < main->player_base[0]) // w
		// 	color = 0xFF0000;
		// if (!side && raycast->mapX >= main->player_base[0]) // e
		// 	color = 0x00FF00;
		// if (side && raycast->mapY < main->player_base[1]) // n
		// 	color = 0x0000FF;
		// if (side && raycast->mapY >= main->player_base[1]) // s
		// 	color = 0x000000;
		draw_line(x, drawStart, drawEnd, 0, raycast);
		int	y;
		y = drawStart;
		raycast->step = 1 * texHeight / lineHeight;
		while (y < drawEnd)
		{
			raycast->texY = (int)raycast->texPos & (texHeight - 1);
			raycast->texPos += raycast->step;
			color = ((int*)(txt->img_data))[texHeight * raycast->texY + raycast->texX];
			pixel_put(raycast->pixel, x, y, color);
			y++;
		}
		x++;
	}
	// printf("\n \n x: %f\n y: %f\n", raycast->posX, raycast->posY);
}

int	render(t_data *main)
{
	// check-keys(main);
	mlx_clear_window(main->raycast->mlx, main->raycast->win);
	mlx_put_image_to_window(main->raycast->mlx, main->raycast->win, main->raycast->pixel->img, 0, 0);
	// mlx_destroy_image(main->raycast->mlx, main->raycast->pixel->img);
	calc(main->raycast, main);
	return (0);
}
