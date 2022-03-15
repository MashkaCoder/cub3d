#include "../cub.h"

void	calc_step_and_sidedist(t_raycast *raycast)
{
	if (raycast->rayDirX < 0)
	{
		raycast->stepX = -1;
		raycast->sideDistX = (raycast->posX - raycast->mapX) * raycast->deltaDistX;
	}
	else
	{
		raycast->stepX = 1;
		raycast->sideDistX = (raycast->mapX + 1.0f - raycast->posX) * raycast->deltaDistX;
		// raycast->sideDistX = (raycast->posX + 1.0f) * raycast->deltaDistX;
	}
	if (raycast->rayDirY < 0)
	{
		raycast->stepY = -1;
		raycast->sideDistY = (raycast->posY - raycast->mapY) * raycast->deltaDistY;
	}
	else
	{
		raycast->stepY = 1;
		raycast->sideDistY = (raycast->mapY + 1.0f - raycast->posY) * raycast->deltaDistY;
		// raycast->sideDistY = (raycast->posY + 1.0ff) * raycast->deltaDistY;
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

void	draw_line(t_raycast *raycast, t_textures *txt, int y, int x)
{
	int	c = 0;

	raycast->step = (1.0f * texHeight / raycast->lineHeight);
	raycast->texPos = (float)((raycast->drawStart - screenHeight / 2 + raycast->lineHeight / 2) * raycast->step);
	while (c < raycast->drawStart)
	{
		pixel_put(raycast->pixel, x, c , raycast->main->ceilling);
		c++;
	}
	while (y <= raycast->drawEnd)
	{
		raycast->texY = (int)raycast->texPos & (texHeight - 1);
		raycast->texPos += raycast->step;
		pixel_put(raycast->pixel, x, y, get_pixel_color(txt, texWidth - raycast->texX - 1, raycast->texY));
		y++;
	}
	while (raycast->drawEnd < screenHeight)
	{
		pixel_put(raycast->pixel, x, raycast->drawEnd , raycast->main->floor);
		raycast->drawEnd++;
	}
}

void	seach_draw_and_txt(t_raycast *raycast)
{
	if (!raycast->side)
	{
		raycast->perpWallDist = raycast->sideDistX - raycast->deltaDistX;
		raycast->wallX = raycast->posY + raycast->perpWallDist * raycast->rayDirY;
	}
	else
	{
		raycast->perpWallDist = raycast->sideDistY - raycast->deltaDistY;
		raycast->wallX = raycast->posX + raycast->perpWallDist * raycast->rayDirX;
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
	t_textures *txt;

	if (!raycast->side && raycast->mapX < raycast->posX) // w
		txt = main->west;
	if (!raycast->side && raycast->mapX >= raycast->posX) // e
		txt = main->east;
	if (raycast->side && raycast->mapY < raycast->posY) // n
		txt = main->north;
	if (raycast->side && raycast->mapY >= raycast->posY) // s
		txt = main->south;
	draw_line(raycast, txt, raycast->drawStart, x);
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
	mlx_put_image_to_window(main->raycast->mlx, main->raycast->win, main->raycast->pixel->img, 0, 0);
	return (0);
}
