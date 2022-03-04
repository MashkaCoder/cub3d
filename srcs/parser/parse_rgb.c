/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoach <scoach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 21:09:51 by scoach            #+#    #+#             */
/*   Updated: 2022/03/04 21:53:44 by scoach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void	ft_conc_tmp(char ***tmp, int i, int aln)
{
	char	*first;
	char	*second;
	char	*now;

	ft_putarr_fd(*tmp, 1);
	if (aln > 2)
	{
		first = ft_strdup((*tmp)[0]);
		second = ft_strdup((*tmp)[1]);
		while (i < aln)
		{
			now = ft_strjoin(second, (*tmp)[i]);
			free(second);
			second = ft_strdup(now);
			free(now);
			i++;
		}
		ft_free_arr(*tmp, aln);
		*tmp = ft_calloc(3, sizeof(char *));
		(*tmp)[0] = ft_strdup(first);
		free(first);
		(*tmp)[1] = ft_strdup(second);
		free(second);
	}
}

void	ft_parse_rgb(t_data *data, char ***tmp, int (*op)[3], int i)
{
	char	**rgb;
	int		num;

	ft_conc_tmp(tmp, 2, ft_arrlen(*tmp));
	rgb = ft_split((*tmp)[1], ',');
	if (rgb == NULL || ft_arrlen(rgb) != 3)
	{
		ft_free_arr(rgb, ft_arrlen(rgb));
		ft_free_arr(*tmp, 2);
		ft_error(data, "RGB format is wrong", 0);
	}
	while (i < 3)
	{
		num = ft_atoi(rgb[i]);
		if (num > 255 || num < 0)
		{
			ft_free_arr(*tmp, 2);
			ft_free_arr(rgb, 3);
			ft_error(data, "RGB must be between 0 and 255", 0);
		}
		(*op)[i] = num;
		i++;
	}
	ft_free_arr(rgb, 3);
}
