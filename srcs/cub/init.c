#include "../cub.h"

void	init_st_rc2(t_data *main, t_raycast *raycast)
{
	if (main->playdir == 'N')
	{
		raycast->dirX = 0;
		raycast->dirY = -1;
	}
	if (main->playdir == 'S')
	{
		raycast->dirX = 0;
		raycast->dirY = 1;
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
}

void	init_st_rc(t_data *main, t_raycast *raycast)
{

	raycast->posX = (float)main->player_base[0] + 0.5;
	raycast->posY = (float)main->player_base[1] + 0.5;
	raycast->main = main;
	raycast->cameraX = 0.0;
	raycast->moveSpeed = 0.09;
	raycast->rotSpeed = 0.07;
	init_st_rc2(main, raycast);
	main->map[main->player_base[1]][main->player_base[0]] = '0';
	raycast->planeX = -raycast->dirY * 0.66;
	raycast->planeY = raycast->dirX * 0.66;
	ft_open_args(main, raycast);
}
