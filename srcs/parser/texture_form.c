/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_form.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chasimir <chasimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:52:46 by scoach            #+#    #+#             */
/*   Updated: 2022/03/08 21:11:24 by chasimir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

// сорри, я немного сюда вмешалась
void	ft_open_args(t_data *data, t_raycast *raycast)
{
	int	img_height;
	int	img_width;

	if (access(data->nswe[0], O_RDONLY) == -1
		|| access(data->nswe[1], O_RDONLY) == -1
		|| access(data->nswe[2], O_RDONLY) == -1
		|| access(data->nswe[3], O_RDONLY) == -1)
		ft_error(data, "Some texture is missing or access is denied\n", 0);
	data->walls = (t_txtr *)malloc(sizeof(t_txtr));
	if (data->walls == NULL)
		ft_error(data, "", 0);
	data->walls->north = mlx_xpm_file_to_image(raycast->mlx, data->nswe[0],
			&img_width, &img_height);
	data->walls->south = mlx_xpm_file_to_image(raycast->mlx, data->nswe[1],
			&img_width, &img_height);
	data->walls->west = mlx_xpm_file_to_image(raycast->mlx, data->nswe[2],
			&img_width, &img_height);
	data->walls->east = mlx_xpm_file_to_image(raycast->mlx, data->nswe[3],
			&img_width, &img_height);
}

void	ft_destroy_images(t_data *data)
{
	mlx_destroy_image(data->raycast->mlx, data->walls->north);
	mlx_destroy_image(data->raycast->mlx, data->walls->south);
	mlx_destroy_image(data->raycast->mlx, data->walls->west);
	mlx_destroy_image(data->raycast->mlx, data->walls->east);
}


// void	ft_open_args(t_data *data, void *mlx)
// {
// 	if (access(data->nswe[0], O_RDONLY) == -1
// 		|| access(data->nswe[1], O_RDONLY) == -1
// 		|| access(data->nswe[2], O_RDONLY) == -1
// 		|| access(data->nswe[3], O_RDONLY) == -1)
// 		ft_error(data, "Some texture is missing or access is denied\n", 0);
// 	data->walls = (t_txtr *)malloc(sizeof(t_txtr));
// 	if (data->walls == NULL)
// 		ft_error(data, "", 0);
// 	data->walls->north = mlx_xpm_file_to_image(mlx, data->nswe[0],
// 			&data->walls->width, &data->walls->height);
// 	data->walls->south = mlx_xpm_file_to_image(mlx, data->nswe[1],
// 			&data->walls->width, &data->walls->height);
// 	data->walls->west = mlx_xpm_file_to_image(mlx, data->nswe[2],
// 			&data->walls->width, &data->walls->height);
// 	data->walls->east = mlx_xpm_file_to_image(mlx, data->nswe[3],
// 			&data->walls->width, &data->walls->height);
// }

// void	ft_destroy_images(t_data *data)
// {
// 	mlx_destroy_image(data->mlx, data->walls->north);
// 	mlx_destroy_image(data->mlx, data->walls->south);
// 	mlx_destroy_image(data->mlx, data->walls->west);
// 	mlx_destroy_image(data->mlx, data->walls->east);
// }
