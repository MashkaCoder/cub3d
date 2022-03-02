# include "../cub.h"
# include "../../mlx/mlx.h"
# include <math.h>

// FOR CUB
// typedef struct s_mlx
// {
// 	void	*mlx;
// 	void	*win;
// }				t_mlx;

// int	free_all(t_mlx *mlx_str)
// {
// 	exit(EXIT_SUCCESS);
// }

// int	key_hook(int keycode, t_mlx *mlx_st)
// {
// 	if (keycode == ESC)
// 		free_all(mlx_st);
// 	return (0);
// }

// int main(int argc, char **argv)
// {
// 	t_mlx	mlx_st;

// 	mlx_st.mlx = mlx_init();
// 	mlx_st.win = mlx_new_window(mlx_st.mlx, 2200, 1200, "ny privet");
// 	mlx_hook(mlx_st.win, 17, 0, free_all, &mlx_st);
// 	mlx_hook(mlx_st.win, 02, 0, key_hook, &mlx_st);
// 	mlx_loop(mlx_st.mlx);
// }

// RAYCASTR (ARTICLE)

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

typedef struct s_data_c
{
	void	*mlx;
	void	*win;
	float	posX;
	float	posY;
	float	dirX;
	float	dirY;
	float	planeX;
	float	planeY;
	float	time;
	float	oldTime;
}				t_data_c;

int worldMap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int	free_all(t_data_c *mlx_str)
{
	exit(EXIT_SUCCESS);
}

int	key_hook(int keycode, t_data_c *main)
{
	if (keycode == ESC)
		free_all(main);
	return (0);
}

void draw_line(int x, int drawStart, int drawEnd, int color, t_data_c *main)
{
	while (drawStart < drawEnd)
	{
		mlx_pixel_put(main->mlx, main->win, x, drawStart, color);
		drawStart++;
	}

}

void	calc(t_data_c *main)
{
	int		x;
	float	cameraX; // cameraX — координата x на плоскости камеры, которую представляет текущая координата x экрана, сделанная таким образом, что правая сторона экрана получает координату 1, центр экрана получает координату 0, а левая сторона экрана получает координату -1. Из этого можно вычислить направление луча, как было объяснено ранее: как сумму вектора направления и части плоского вектора. Это необходимо сделать как для координат x, так и для y вектора (поскольку добавление двух векторов — это добавление их координат x и добавление их координат y).
	float	rayDirX;
	float	rayDirY;
	int		mapX; // тек клетка, где находится луч
	int		mapY;
	float	sideDistX; // расст, кот должен пройти луч от начальной позиции до первой стороны х/у
	float	sideDistY;
	float	deltaDistX; //расст, кот должен пройти луч от 1 стороны х/у до след стороны х/у
	float	deltaDistY;
	float	perpWallDist; // для выч длины луча
	int		stepX; // в каком направлении делать шаг по оси x или y (либо +1, либо -1)
	int		stepY;
	int		hit; // индиф удара в стену (индик заверш цикла)
	int		side; // удар в стену x/y x = 0, y = 1
	int		lineHeight; //высота вертикальной линии, которая должна быть нарисована
	int		drawStart; // начало отрисовки
	int		drawEnd; //конец
	int		color;


	x = 0;
	while (x < screenWidth)
	{
		// вычисляем позицию и направление
		cameraX = 2 * x / (float)screenWidth - 1;//координата x в пространстве камеры
		rayDirX = main->dirX + main->planeX * cameraX;
		rayDirY = main->dirY + main->planeY * cameraX;
		mapX = (int)main->posX;
		mapY = (int)main->posY;
		hit = 0;
		deltaDistX = fabs(1 / rayDirX);
		deltaDistY = fabs(1 / rayDirY);
		// вычисл нач sideDistX/Y (расст до перв стены)
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (main->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - main->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (main->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - main->posY) * deltaDistY;
		}
		// теперь начинается сам алгом
		//  Это цикл, каждый раз увеличивающий луч на 1 квадрат, пока не будет достигнута стена.
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Проверяем, попал ли луч в стену
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}
		//  Рассчитываем расстояние, спроецированное на направление камеры (евклидово расстояние дало бы эффект рыбьего глаза!)
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		//Рассчитываем высоту линии для рисования на экране
		lineHeight = (int)(screenHeight / perpWallDist);
		drawStart = -lineHeight / 2 + screenHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;
		if (worldMap[mapY][mapX] == 1)
			color = 0xFF0000;
		else if (worldMap[mapY][mapX] == 2)
			color = 0x00FF00;
		else if (worldMap[mapY][mapX] == 3)
			color = 0x0000FF;
		else if (worldMap[mapY][mapX] == 4)
			color = 0xFFFFFF;
		else
			color = 0xFFFF00;
		// придать сторонам x и y разную яркость
		if (side == 1)
			color = color / 2;
		draw_line(x, drawStart, drawEnd, color, main);

		x++;

	}

}


int	render(t_data_c *main)
{
	calc(main);
}

int	main(int argc, char **argv)
{
	t_data_c	main;

	main.mlx = mlx_init();
	main.posX = 22;
	main.posY = 12;
	main.dirX = -1;
	main.dirY = 0;
	main.planeX = 0;
	main.planeY = 0.66;
	main.time = 0;
	main.oldTime = 0;
	main.win = mlx_new_window(main.mlx, screenWidth, screenHeight, "ny privet");
	mlx_loop_hook(main.mlx, render, &main);
	mlx_hook(main.win, 17, 0, free_all, &main);
	mlx_hook(main.win, 02, 0, key_hook, &main);
	mlx_loop(main.mlx);
}
