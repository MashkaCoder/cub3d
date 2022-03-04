/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_form.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoach <scoach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:52:46 by scoach            #+#    #+#             */
/*   Updated: 2022/03/04 13:45:38 by scoach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	ft_get_textures(t_data *data, void *mlx, t_txtr *walls)
{
	if (access(data->nswe[0], O_RDONLY) == -1
		|| access(data->nswe[1], O_RDONLY) == -1
		|| access(data->nswe[2], O_RDONLY) == -1
		|| access(data->nswe[3], O_RDONLY) == -1)
		ft_error(data, "Some texture is missing or access is denied\n", 0);
	walls->north = mlx_xpm_file_to_image(mlx, data->nswe[0],
			&walls->width, &walls->height);
	walls->south = mlx_xpm_file_to_image(mlx, data->nswe[1],
			&walls->width, &walls->height);
	walls->west = mlx_xpm_file_to_image(mlx, data->nswe[2],
			&walls->width, &walls->height);
	walls->east = mlx_xpm_file_to_image(mlx, data->nswe[3],
			&walls->width, &walls->height);
}

void	ft_destroy_images(t_data *data)
{
	mlx_destroy_image(data->mlx, data->walls->north);
	mlx_destroy_image(data->mlx, data->walls->south);
	mlx_destroy_image(data->mlx, data->walls->west);
	mlx_destroy_image(data->mlx, data->walls->east);
}
