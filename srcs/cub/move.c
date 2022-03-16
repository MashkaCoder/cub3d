#include "../cub.h"

void	move_a(t_raycast *raycast)
{
	if(raycast->main->map[(int)raycast->posY][(int)(raycast->posX - raycast->planeX * 0.11f)] != '1')
			raycast->posX -= raycast->planeX * raycast->moveSpeed;
	if(raycast->main->map[(int)(raycast->posY - raycast->planeY * 0.11f)][(int)raycast->posX] != '1')
		raycast->posY -= raycast->planeY * raycast->moveSpeed;
}

void	move_d(t_raycast *raycast)
{
	printf("hello d\n");
	if(raycast->main->map[(int)raycast->posY][(int)(raycast->posX + raycast->planeX * (float)0.11)] != '1')
			raycast->posX += raycast->planeX * raycast->moveSpeed;
	if(raycast->main->map[(int)(raycast->posY + raycast->planeY * (float)0.11)][(int)(raycast->posX)] != '1')
		raycast->posY += raycast->planeY * raycast->moveSpeed;
}

void	move_s(t_raycast *raycast)
{
	if(raycast->main->map[(int)raycast->posY][(int)(raycast->posX - raycast->dirX * 0.11f)] != '1')
			raycast->posX -= raycast->dirX * raycast->moveSpeed;
	if(raycast->main->map[(int)(raycast->posY - raycast->dirY * (float)0.11)][(int)raycast->posX] != '1')
		raycast->posY -= raycast->dirY * raycast->moveSpeed;
}

void	move_w(t_raycast *raycast)
{
	printf("hello w\n");
	if(raycast->main->map[(int)raycast->posY][(int)(raycast->posX + raycast->dirX * 0.11f)] != '1')
			raycast->posX += raycast->dirX * raycast->moveSpeed;
	if(raycast->main->map[(int)(raycast->posY + raycast->dirY * 0.11f)][(int)raycast->posX] != '1')
		raycast->posY += raycast->dirY * raycast->moveSpeed;
}

