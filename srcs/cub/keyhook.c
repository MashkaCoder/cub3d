// # include "../cub.h"

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
		if(raycast->main->map[(int)raycast->posY][(int)(raycast->posX - raycast->dirX * 0.11f)] != '1')
			raycast->posX -= raycast->dirX * raycast->moveSpeed;
		if(raycast->main->map[(int)(raycast->posY - raycast->dirY * (float)0.11)][(int)raycast->posX] != '1')
			raycast->posY -= raycast->dirY * raycast->moveSpeed;
	}
	if (keycode == A)
	{
		if(raycast->main->map[(int)raycast->posY][(int)(raycast->posX - raycast->planeX * 0.11f)] != '1')
			raycast->posX -= raycast->planeX * raycast->moveSpeed;
		if(raycast->main->map[(int)(raycast->posY - raycast->planeY * 0.11f)][(int)raycast->posX] != '1')
			raycast->posY -= raycast->planeY * raycast->moveSpeed;
		// strafe(raycast, -1);
	}
	if (keycode == D)
	{
		if(raycast->main->map[(int)raycast->posY][(int)(raycast->posX + raycast->planeX * (float)0.11)] != '1')
			raycast->posX += raycast->planeX * raycast->moveSpeed;
			// raycast->posX -= raycast->posX + raycast->dirX * raycast->moveSpeed * -1;
		if(raycast->main->map[(int)(raycast->posY + raycast->planeY * (float)0.11)][(int)(raycast->posX)] != '1')
			raycast->posY += raycast->planeY * raycast->moveSpeed;
			// raycast->posY -= raycast->posY + raycast->dirY * raycast->moveSpeed * 1;
		// strafe(raycast, 1);
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
