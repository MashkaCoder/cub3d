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

void	init_key(t_raycast *raycast)
{
	t_keys	keys;

	ft_memset(&keys, 0, sizeof(t_keys));
	raycast->keys = &keys;
	printf("init %p\n", raycast->keys);
	printf("init %p\n", &keys);
}

void	init_st_rc(t_data *main, t_raycast *raycast)
{
	raycast->posX = (float)main->player_base[0] + 0.5;
	raycast->posY = (float)main->player_base[1] + 0.5;
	raycast->main = main;
	raycast->cameraX = 0.0;
	raycast->moveSpeed = 0.09;
	raycast->rotSpeed = 0.07;
	raycast->wallX = 0;
	raycast->texX = 0;
	init_st_rc2(main, raycast);
	main->map[main->player_base[1]][main->player_base[0]] = '0';
	raycast->planeX = -raycast->dirY * 0.66;
	raycast->planeY = raycast->dirX * 0.66;
	init_key(raycast);
	printf("%p\n", raycast->keys);
	init_txt(main);
}

void	init_txt(t_data *main)
{
	main->north = malloc(sizeof(t_textures));
	main->south = malloc(sizeof(t_textures));
	main->east = malloc(sizeof(t_textures));
	main->west = malloc(sizeof(t_textures));
	load_txt(main);
}

void	open_txt(t_data *main, t_textures *txt, char *path)
{
	if (access(path, O_RDONLY) == -1)
		ft_error(main, "Some texture is missing or access is denied\n", 0);
	txt->img_ptr = mlx_xpm_file_to_image(main->raycast->mlx, path, &txt->width, &txt->height);
	txt->img_data = mlx_get_data_addr(txt->img_ptr, &txt->bpp, &txt->line_len, &txt->endian);
	printf("popa2\n");
}

void	load_txt(t_data *main)
{
	open_txt(main, main->north, main->nswe[0]);
	open_txt(main, main->south, main->nswe[1]);
	open_txt(main, main->west, main->nswe[2]);
	open_txt(main, main->east, main->nswe[3]);
}
