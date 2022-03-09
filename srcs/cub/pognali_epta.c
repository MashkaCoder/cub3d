#include "../cub.h"

void	init_st_rc(t_data *main, t_raycast *raycast)
{
	raycast->posX = (float)main->player_base[0];
	raycast->posY = (float)main->player_base[1];
	raycast->moveSpeed = 0.1;
	raycast->rotSpeed = 0.1;
	if (main->playdir == 'N')
	{
		raycast->dirX = 0;
		raycast->dirY = 1;
	}
	if (main->playdir == 'S')
	{
		raycast->dirX = 0;
		raycast->dirY = -1;
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
	raycast->planeX = raycast->dirY * 0.66;
	raycast->planeY = -raycast->dirX * 0.66;
	ft_open_args(main, raycast);
}

int	free_all(void)
{
	exit(EXIT_SUCCESS);
}

int	keyhook(int keycode, t_raycast *raycast)
{
	if (keycode == ESC)
		free_all();
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
		raycast->sideDistX = (raycast->posX + 1.0) * raycast->deltaDistX;
	}
	if (raycast->rayDirY < 0)
	{
		raycast->stepY = -1;
		raycast->sideDistY = (raycast->posY - raycast->mapY) * raycast->deltaDistY;
	}
	else
	{
		raycast->stepY = 1;
		raycast->sideDistY = (raycast->posY + 1.0) * raycast->deltaDistY;
	}
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
		raycast->cameraX = 2 * x / (float)screenWidth - 1;
		raycast->rayDirX = raycast->dirX + raycast->planeX * raycast->cameraX;
		raycast->rayDirY = raycast->dirY + raycast->planeY * raycast->cameraX;
		raycast->deltaDistX = fabs(1 / raycast->rayDirX);
		raycast->deltaDistY = fabs(1 / raycast->rayDirY);
		raycast->mapX = main->player_base[0];
		raycast->mapY = main->player_base[1];
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
				raycast->sideDistX += raycast->deltaDistX;
				raycast->mapX += raycast->stepX;
				side = 0;
			}
			if (main->map[raycast->mapX][raycast->mapY] == 1)
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


		x++;
	}

}

int	render(t_data *main)
{
	calc(main->raycast, main);
	return (0);
}

// int	dolznoBitVmain(t_data *main, t_raycast *raycast)
// {
// 	raycast->mlx = mlx_init();
// 	init_st_rc(main, raycast);
// 	raycast->win = mlx_new_window(raycast->mlx, screenWidth, screenHeight, "privetyli");
// 	mlx_hook(raycast->win, 2, 0, keyhook, raycast);
// 	mlx_hook(raycast->win, 2, 0, free_all, raycast);
// 	mlx_loop(raycast->mlx);
// 	return (0);
// }
