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
