#include "../cub.h"

int	free_all(void)
{
	exit(EXIT_SUCCESS);
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
		if(raycast->main->map[(int)raycast->posY][(int)(raycast->posX - raycast->planeX * (float)0.11)] != '1')
			raycast->posX -= raycast->planeX * raycast->moveSpeed;
		if(raycast->main->map[(int)(raycast->posY - raycast->planeY * (float)0.11)][(int)raycast->posX] != '1')
			raycast->posY -= raycast->planeY * raycast->moveSpeed;

	}
	if (keycode == D)
	{
		if(raycast->main->map[(int)raycast->posY][(int)(raycast->posX + raycast->planeX * (float)0.11)] != '1')
			raycast->posX += raycast->planeX * raycast->moveSpeed;
		if(raycast->main->map[(int)(raycast->posY + raycast->planeY * (float)0.11)][(int)(raycast->posX)] != '1')
			raycast->posY += raycast->planeY * raycast->moveSpeed;

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
	while (c < drawStart)
	{
		// pixel_put(raycast->pixel, x, c, raycast->main->ceilling);
		// pixel_put(raycast, x, c, raycast->main->ceilling);
		mlx_pixel_put(raycast->mlx, raycast->win, x, c, raycast->main->ceilling);
		c++;
	}
	while (drawStart <= drawEnd)
	{
		// pixel_put(raycast->pixel, x, drawStart, color);
		// pixel_put(raycast, x, drawStart, color);
		mlx_pixel_put(raycast->mlx, raycast->win, x, drawStart, color);
		drawStart++;
	}
	while (drawEnd < screenHeight)
	{
		// pixel_put(raycast->pixel, x, drawEnd, raycast->main->floor);
		// pixel_put(raycast, x, drawEnd, raycast->main->floor);
		drawEnd++;
		mlx_pixel_put(raycast->mlx, raycast->win, x, drawEnd, raycast->main->floor);
	}
}

void	dir_and_dist(t_raycast *raycast, t_data *main, int x)
{
	raycast->cameraX = 2 * x / (float)screenWidth - 1;
	raycast->rayDirX = raycast->dirX + raycast->planeX * raycast->cameraX;
	raycast->rayDirY = raycast->dirY + raycast->planeY * raycast->cameraX;
	raycast->deltaDistX = fabs(1 / raycast->rayDirX);
	raycast->deltaDistY = fabs(1 / raycast->rayDirY);
	raycast->mapX = main->player_base[0];
	raycast->mapY = main->player_base[1];
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
		if (side == 0)
			raycast->perpWallDist = raycast->sideDistX - raycast->deltaDistX;
		else
			raycast->perpWallDist = raycast->sideDistY - raycast->deltaDistY;
		lineHeight = (int)(screenHeight / raycast->perpWallDist);
		drawStart = -lineHeight / 2 + screenHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;
		int	color;
		if (!side && raycast->mapX < main->player_base[0]) // w
			color = 0xFF0000;
		if (!side && raycast->mapX >= main->player_base[0]) // e
			color = 0x00FF00;
		if (side && raycast->mapY < main->player_base[1]) // n
			color = 0x0000FF;
		if (side && raycast->mapY >= main->player_base[1]) // s
			color = 0x000000;
		draw_line(x, drawStart, drawEnd, color, raycast);
		x++;
	}
	// mlx_put_image_to_window(main->raycast->mlx, main->raycast->win, main->raycast->pixel->img, 0, 0);
}

int	render(t_data *main)
{
	// check-keys(main);
	mlx_clear_window(main->raycast->mlx, main->raycast->win);
	calc(main->raycast, main);
	return (0);
}
