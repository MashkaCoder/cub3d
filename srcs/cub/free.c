/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chasimir <chasimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:25:25 by chasimir          #+#    #+#             */
/*   Updated: 2022/03/17 18:43:14 by chasimir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	free_all_raycast(t_data *main)
{
	if (main->raycast->keys)
		free(main->raycast->keys);
	free_txtr(main);
	mlx_destroy_image(main->raycast->mlx, main->raycast->pixel->img);
	mlx_destroy_window(main->raycast->mlx, main->raycast->win);
	if (main->raycast->pixel)
		free(main->raycast->pixel);
	if (main->raycast)
		free(main->raycast);
}

void	free_txtr(t_data *main)
{
	if (main->west)
		free(main->west);
	if (main->east)
		free(main->east);
	if (main->north)
		free(main->north);
	if (main->south)
		free(main->south);
}
