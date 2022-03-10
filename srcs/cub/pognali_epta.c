#include "../cub.h"
#include <string.h>
void	init_st_rc(t_data *main, t_raycast *raycast)
{
	raycast->posX = (float)main->player_base[0] + 0.5;
	raycast->posY = (float)main->player_base[1] + 0.5;
	raycast->main = main;
	raycast->cameraX = 0.0;
	raycast->moveSpeed = 0.5;
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
	main->map[main->player_base[1]][main->player_base[0]] = '0';
	int i;
	i = 0;
	while(main->map[i])
	{
		printf("%s\n", main->map[i]);
		i++;
	}
	raycast->planeX = raycast->dirY * 0.66;
	raycast->planeY = -raycast->dirX * 0.66;
	ft_open_args(main, raycast);
	// printf("init %p\n", raycast);
}

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
	if (keycode == AR_RIGHT)
	{
		raycast->dirX = raycast->dirX * cos(-raycast->rotSpeed) - raycast->dirY * sin(-raycast->rotSpeed);
		raycast->dirY = oldDirX * sin(-raycast->rotSpeed) + raycast->dirY * cos(-raycast->rotSpeed);
		raycast->planeX = raycast->planeX * cos(-raycast->rotSpeed) - raycast->planeY * sin(-raycast->rotSpeed);
		raycast->planeY = oldPlaneX * sin(-raycast->rotSpeed) + raycast->planeY * cos(raycast->rotSpeed);
	}
	if (keycode == AR_LEFT)
	{
		raycast->dirX = raycast->dirX * cos(raycast->rotSpeed) - raycast->dirY * sin(raycast->rotSpeed);
		raycast->dirY = oldDirX * sin(raycast->rotSpeed) + raycast->dirY * cos(raycast->rotSpeed);
		raycast->planeX = raycast->planeX * cos(raycast->rotSpeed) - raycast->planeY * sin(raycast->rotSpeed);
		raycast->planeY = oldPlaneX * sin(raycast->rotSpeed) + raycast->planeY * cos(raycast->rotSpeed);
	}
	if (keycode == S)
	{
		if(raycast->main->map[(int)raycast->posY][(int)(raycast->posX + raycast->dirX * raycast->moveSpeed)] != '1')
			raycast->posX += raycast->dirX * raycast->moveSpeed;
		printf("x: %d\n y:%d\n", (int)(raycast->posX + raycast->dirX * raycast->moveSpeed), (int)raycast->posY );
		if(raycast->main->map[(int)(raycast->posY + raycast->dirY * raycast->moveSpeed)][(int)raycast->posX] != '1')
			raycast->posY += raycast->dirY * raycast->moveSpeed;
	}
	if (keycode == W)
	{
		if(raycast->main->map[(int)(raycast->posX - raycast->dirX * raycast->moveSpeed)][(int)raycast->posY] != '1')
			raycast->posX -= raycast->dirX * raycast->moveSpeed;
		if(raycast->main->map[(int)raycast->posX][(int)(raycast->posY - raycast->dirY * raycast->moveSpeed)] != '1')
			raycast->posY -= raycast->dirY * raycast->moveSpeed;
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

void draw_line(int x, int drawStart, int drawEnd, int color, t_raycast *raycast)
{
	int	c;

	c = 0;
	while (c < drawStart)
	{
		mlx_pixel_put(raycast->mlx, raycast->win, x, c, raycast->main->ceilling);
		c++;
	}
	while (drawStart <= drawEnd)
	{
		mlx_pixel_put(raycast->mlx, raycast->win, x, drawStart, color);
		drawStart++;
	}
	while (drawEnd < screenHeight)
	{
		mlx_pixel_put(raycast->mlx, raycast->win, x, drawEnd, raycast->main->floor);
		drawEnd++;
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
			color = 0x549FB8;
		if (!side && raycast->mapX >= main->player_base[0]) // e
			color = 0xB22222;
		if (side && raycast->mapY < main->player_base[1]) // n
			color = 0x228B22;
		if (side && raycast->mapY >= main->player_base[1]) // s
			color = 0x40E0D0;
		draw_line(x, drawStart, drawEnd, color, raycast);
		x++;
	}

}

int	render(t_data *main)
{
	mlx_clear_window(main->raycast->mlx, main->raycast->win);
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
