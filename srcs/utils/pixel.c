#include "../cub.h"

// void	pixel_put(t_raycast *raycast, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = raycast->addr + (y * raycast->line_len + x * (raycast->bpp / 8));
// 	*(unsigned int*)dst = color;
// }

void	pixel_put(t_pixel *pixel, int x, int y, int color)
{
	char	*dst;

	dst = pixel->addr + (y * pixel->line_len + x * (pixel->bpp / 8));
	*(unsigned int*)dst = color;
}
