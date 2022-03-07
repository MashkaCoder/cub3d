# include "../cub.h"
# include "../../mlx/mlx.h"
# include <math.h>
#include <sys/time.h>
#include <stdio.h>

#define textWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 580

typedef struct	s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct s_data_c
{
	t_img			img;
	void			*t1;
	void			*t2;
	void			*t3;
	void			*t4;
	void			*mlx;
	void			*win;
	float			posX;
	float			posY;
	float			dirX;
	float			dirY;
	float			planeX;
	float			planeY;
	unsigned long	time;
	unsigned long	oldTime;
	float			moveSpeed; //мод скор
	float			rotSpeed;
	int				**texture;
	int				**bufer;
}				t_data_c;

unsigned long	get_time(void);
void			calc(t_data_c *main);
int				key_hook(int keycode, t_data_c *main);
void			draw_line(int x, int drawStart, int drawEnd, int color, t_data_c *main);
void			load_texture(t_data_c *z);

int worldMap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, //0
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, //1
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, //2
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, //3
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1}, //4
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1}, //5
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1}, //6
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1}, //7
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1}, //8
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, //9
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, //10
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, //11
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, //12
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, //13
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, //14
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, //15
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, //16
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, //17
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, //18
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, //19
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, //20
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, //21
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, //22
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}  //23
};

int	free_all(t_data_c *mlx_str)
{
	exit(EXIT_SUCCESS);
}

int	key_hook(int keycode, t_data_c *main)
{
	float oldDir = main->dirX;
	float oldPlaneX = main->planeX;
	if (keycode == ESC)
		free_all(main);
	else if (keycode == W)
	{
		if (!worldMap[(int)(main->posX + main->dirX * main->moveSpeed)][(int)main->posY])
			main->posX += main->dirX * main->moveSpeed;
		if (!worldMap[(int)(main->posX)][(int)(main->posY  + main->dirY * main->moveSpeed)])
			main->posY += main->dirY * main->moveSpeed;
	}
	else if (keycode == S)
	{
		if (!worldMap[(int)(main->posX - main->dirX * main->moveSpeed)][(int)main->posY])
			main->posX -= main->dirX * main->moveSpeed;
		if (!worldMap[(int)(main->posX)][(int)(main->posY - main->dirY * main->moveSpeed)])
			main->posY -= main->dirY * main->moveSpeed;
	}
	else if (keycode == D)
	{
		// float oldDir = main->dirX;
		// float oldPlaneX = main->planeX;
		main->dirX = main->dirX * cos(-main->rotSpeed) - main->dirY * sin(-main->rotSpeed);
		main->dirY = oldDir * sin(-main->rotSpeed) + main->dirY * cos(-main->rotSpeed);
		// float oldPlaneX = main->planeX;
		main->planeX = main->planeX * cos(-main->rotSpeed) - main->planeY * sin(-main->rotSpeed);
		main->planeY = oldPlaneX * sin(-main->rotSpeed) + main->planeY * cos(-main->rotSpeed);

	}
	else if (keycode == A)
	{
		// float oldDir = main->dirX;
		main->dirX = main->dirX * cos(main->rotSpeed) - main->dirY * sin(main->rotSpeed);
		main->dirY = oldDir * sin(main->rotSpeed) + main->dirY * cos(main->rotSpeed);
		// float oldPlaneX = main->planeX;
		main->planeX = main->planeX * cos(main->rotSpeed) - main->planeY * sin(main->rotSpeed);
		main->planeY = oldPlaneX * sin(main->rotSpeed) + main->planeY * cos(main->rotSpeed);
	}
	return (0);
}

void draw_line(int x, int drawStart, int drawEnd, int color, t_data_c *main)
{
	while (drawStart <= drawEnd)
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
	float	frameTime; // время, которое занял кадр
	// пол

	float	posZ; // вертик положение камеры
	int		p; //тек поз у относ центра экрана (горизонта)
	float	rowDistance; // гор рассста от камеры до пола для тек строки
	int y;
	y = 0;
	while (y < screenHeight)
	{
		// rayDir для крайнего левого (x = 0) и крайнего правого (x = w)
		float	rayDirX0 = main->dirX - main->planeX;
		float	rayDirY0 = main->dirY - main->planeY;
		float	rayDirX1 = main->dirX + main->planeX;
		float	rayDirY1 = main->dirY + main->planeY; // Текущая позиция y относительно центра экрана (горизонта)
		p = y - screenHeight / 2;
		posZ = screenHeight * 0.5;
		rowDistance = posZ/p;
		// вычислить реальный вектор шага, который мы должны добавить для каждого x (параллельно плоскости камеры)
		// сложение шаг за шагом позволяет избежать умножения с весом во внутреннем цикле
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / screenWidth;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / screenHeight; // реальные координаты крайнего левого столбца. Это будет обновляться по мере того, как мы шагаем вправо.
		float floorX = main->posX + rowDistance * rayDirX0;
		float floorY = main->posY + rowDistance * rayDirY0;
		x = 0;
		while (x < screenWidth)
		{
			// 0xFF0000
			color = 0x30ba8f;
			int cellX = (int)floorX;
			int cellY = (int)floorY; // коорд ячейки
			floorX += floorStepX;
			floorY += floorStepY;
			// draw_line(x, y, y, color, main);
			x++;


		}
		y++;

	}


	// стены
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
			// perpWallDist = (sideDistX - deltaDistX);
			perpWallDist = (mapX - main->posX + (1 - stepX) / 2) / rayDirX;
		else
			// perpWallDist = (sideDistY - deltaDistY);
			perpWallDist = (mapY - main->posY + (1 - stepY) / 2) / rayDirY;
		//Рассчитываем высоту линии для рисования на экране
		lineHeight = (int)(screenHeight / perpWallDist);
		// drawStart = -lineHeight / 2 + screenHeight / 2;
		// if (drawStart < 0)
		// 	drawStart = 0;
		// drawEnd = lineHeight / 2 + screenHeight / 2;
		// if (drawEnd >= screenHeight)
		// 	drawEnd = screenHeight - 1;
		// if (worldMap[mapY][mapX] == 1)
		// 	color = 0xFF0000;
		// else if (worldMap[mapY][mapX] == 2)
		// 	color = 0x00FF00;
		// else if (worldMap[mapY][mapX] == 3)
		// 	color = 0x0000FF;
		// else if (worldMap[mapY][mapX] == 4)
		// 	color = 0xFFFFFF;
		// else
		// 	color = 0xFFFF00;
		// // придать сторонам x и y разную яркость
		// if (side == 1)
		// 	color = color / 2;
		// draw_line(x, drawStart, drawEnd, color, main);
		// x++;
		// texturing calculations
		int texNum = worldMap[mapX][mapY];

		// calculate value of wallX
		double wallX;
		if (side == 0)
			wallX = main->posY + perpWallDist * rayDirY;
		else
			wallX = main->posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		// x coordinate on the texture
		int texX = (int)(wallX * (double)textWidth);
		if (side == 0 && rayDirX > 0)
			texX = textWidth - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = textWidth - texX - 1;

		// How much to increase the texture coordinate perscreen pixel
		double step = 1.0 * texHeight / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			int color = main->texture[texNum][texHeight * texY + texX];
			// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (side == 1)
				color = (color >> 1) & 8355711;
			main->bufer[y][x] = color;
		}
		x++;
	}

}

void	draw(t_data_c *main)
{
	for (int y = 0; y < screenHeight; y++)
	{
		for (int x = 0; x < screenWidth; x++)
		{
			main->img.data[y * screenWidth + x] = main->bufer[y][x];
		}
	}
	mlx_put_image_to_window(main->mlx, main->win, main->img.img, 0, 0);
}

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	render(t_data_c *main)
{
	calc(main);
	draw(main);
	mlx_clear_window(main->mlx, main->win);
	return (0);
}

void	load_image(t_data *main, int *texture, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(main->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	for (int y = 0; y < img->img_height; y++)
	{
		for (int x = 0; x < img->img_width; x++)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
	mlx_destroy_image(main->mlx, img->img);
}

void	load_texture(t_data_c *z)
{
	t_img	img;
	load_image(z, z->texture[0], "textures/wall1.XPM", &img);
	printf("ppp\n");
	load_image(z, z->texture[1], "textures/wall2.XPM", &img);
	load_image(z, z->texture[2], "textures/wall2.XPM", &img);
	load_image(z, z->texture[3], "textures/wall2.XPM", &img);
}

int	main(int argc, char **argv)
{
	t_data_c	main;

	main.mlx = mlx_init();
	main.posX = 12;
	main.posY = 5;
	main.dirX = -1;
	main.dirY = 0;
	main.planeX = 0;
	main.planeY = 0.66;
	main.moveSpeed = 0.1; //значение константы в квадратах/секунду
	main.rotSpeed = 0.1; //значение константы в радианах/секунду
	main.bufer = (int **)malloc(sizeof(int *) * screenHeight);
	for (int i = 0; i < screenHeight; i++)
		main.bufer[i] = (int *)malloc(sizeof(int) * screenWidth);
	if (!(main.texture = (int **)malloc(sizeof(int *) * 4)))
		return (-1);
	for (int i = 0; i < 8; i++)
	{
		if (!(main.texture[i] = (int *)malloc(sizeof(int) * (texHeight * textWidth))))
			return (-1);
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < texHeight * textWidth; j++)
		{
			main.texture[i][j] = 0;
		}
	}
	main.win = mlx_new_window(main.mlx, screenWidth, screenHeight, "ny privet");
	load_texture(&main);
	mlx_loop_hook(main.mlx, &render, &main);
	mlx_hook(main.win, 02, 0, &key_hook, &main);
	mlx_hook(main.win, 17, 0, free_all, &main);
	mlx_loop(main.mlx);
	return (0);
}
