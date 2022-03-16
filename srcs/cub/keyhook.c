#include "../cub.h"

int	free_all(void)
{
	exit(EXIT_SUCCESS);
}

int	keypress(int keycode, t_keys *keys)
{
	// printf("hello\n");
	if (keycode == ESC)
		free_all();
	if (keycode == AR_LEFT)
		keys->key_la = 1;
	if (keycode == AR_RIGHT)
		keys->key_ra = 1;
	if (keycode == S)
		keys->key_s = 1;
	if (keycode == A)
		keys->key_a = 1;
	if (keycode == D)
		keys->key_d = 1;
	if (keycode == W)
		{
			keys->key_w = 1;
			printf("press w %d\n", keys->key_w);
		}
	return (0);
}

int	keyrelease(int keycode, t_keys *keys)
{
	if (keycode == AR_LEFT)
		keys->key_la = 0;
	if (keycode == AR_RIGHT)
		keys->key_ra = 0;
	if (keycode == S)
		keys->key_s = 0;
	if (keycode == A)
		keys->key_a = 0;
	if (keycode == D)
		keys->key_d = 0;
	if (keycode == W)
		keys->key_w = 0;
	return (0);
}

void	rotate(t_raycast *raycast, char dir)
{
	float	oldDirX;
	float	oldPlaneX;

	oldDirX = raycast->dirX;
	oldPlaneX = raycast->planeX;
	if (dir == 'l')
	{
		raycast->dirX = raycast->dirX * cos(-raycast->rotSpeed) - raycast->dirY * sin(-raycast->rotSpeed);
		raycast->dirY = oldDirX * sin(-raycast->rotSpeed) + raycast->dirY * cos(-raycast->rotSpeed);
		raycast->planeX = raycast->planeX * cos(-raycast->rotSpeed) - raycast->planeY * sin(-raycast->rotSpeed);
		raycast->planeY = oldPlaneX * sin(-raycast->rotSpeed) + raycast->planeY * cos(raycast->rotSpeed);
	}
	if (dir == 'r')
	{
		raycast->dirX = raycast->dirX * cos(raycast->rotSpeed) - raycast->dirY * sin(raycast->rotSpeed);
		raycast->dirY = oldDirX * sin(raycast->rotSpeed) + raycast->dirY * cos(raycast->rotSpeed);
		raycast->planeX = raycast->planeX * cos(raycast->rotSpeed) - raycast->planeY * sin(raycast->rotSpeed);
		raycast->planeY = oldPlaneX * sin(raycast->rotSpeed) + raycast->planeY * cos(raycast->rotSpeed);
	}

}
void	key_event(t_raycast *raycast, t_keys *keys)
{
	if (keys->key_a)
		move_a(raycast);
	if (keys->key_d)
		move_d(raycast);
	if (keys->key_s)
		move_s(raycast);
	if (keys->key_w)
		move_w(raycast);
	// if (keys->key_la)
	// 	rotate_l(raycast);
	// if (keys->key_ra)
	// 	rotate_r(raycast);
	if (keys->key_la)
		rotate(raycast, 'l');
	if (keys->key_ra)
		rotate(raycast, 'r');
}
