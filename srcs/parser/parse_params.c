/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoach <scoach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:29:53 by scoach            #+#    #+#             */
/*   Updated: 2022/03/04 15:32:44 by scoach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void	ft_parse_rgb(t_data *data, char **tmp, int (*op)[3])
{
	char	**rgb;
	int		i;
	int		num;

	rgb = ft_split(tmp[1], ',');
	if (rgb == NULL || ft_arrlen(rgb) != 3)
	{
		ft_free_arr(rgb, ft_arrlen(rgb));
		ft_free_arr(tmp, 2);
		ft_error(data, "RGB format is wrong", 0);
	}
	i = 0;
	while (i < 3)
	{
		num = ft_atoi(rgb[i]);
		if (num > 255 || ft_atoi(rgb[0]) < 0)
		{
			ft_free_arr(tmp, 2);
			ft_free_arr(rgb, 3);
			ft_error(data, "RGB must be between 0 and 255", 0);
		}
		(*op)[i] = num;
		i++;
	}
	ft_free_arr(rgb, 3);
}

static int	ft_data_write2(t_data *data, char **tmp)
{
	if (tmp[0][0] == 'N' && tmp[0][1] == 'O' && data->nswe[0] == NULL)
	{
		data->nswe[0] = ft_strdup(tmp[1]);
		if (data->nswe[0] == NULL)
			return (1);
	}
	else if (tmp[0][0] == 'S' && tmp[0][1] == 'O' && data->nswe[1] == NULL)
	{
		data->nswe[1] = ft_strdup(tmp[1]);
		if (data->nswe[1] == NULL)
			return (1);
	}
	else if (tmp[0][0] == 'W' && tmp[0][1] == 'E' && data->nswe[2] == NULL)
	{
		data->nswe[2] = ft_strdup(tmp[1]);
		if (data->nswe[2] == NULL)
			return (1);
	}
	else if (tmp[0][0] == 'E' && tmp[0][1] == 'A' && data->nswe[3] == NULL)
	{
		data->nswe[3] = ft_strdup(tmp[1]);
		if (data->nswe[3] == NULL)
			return (1);
	}
	else
		return (1);
	return (0);
}

static int	ft_data_write(t_data *data, char **tmp, int strln)
{
	if (strln == 1)
	{
		if (tmp[0][0] == 'F' && data->floor[0] == -1)
			ft_parse_rgb(data, tmp, &(data->floor));
		else if (tmp[0][0] == 'C' && data->ceilling[0] == -1)
			ft_parse_rgb(data, tmp, &(data->ceilling));
		else
			return (1);
	}
	else
		return (ft_data_write2(data, tmp));
	return (0);
}

static void	ft_check_write_params(t_data *data, char **line, int *check)
{
	char	**tmp;
	int		sln;

	if (line == NULL || (*line)[0] == '\n' || (*line)[0] == '\0')
		return ;
	tmp = ft_split(*line, ' ');
	if (tmp == NULL)
	{
		free(*line);
		ft_error(data, "ft_split error", 0);
	}
	sln = ft_strlen(tmp[0]);
	if (ft_arrlen(tmp) != 2 || sln > 2 || sln < 1
		|| ft_data_write(data, tmp, sln))
	{
		ft_free_arr(tmp, 2);
		ft_error(data, "Wrong map parameters", 0);
	}
	ft_free_arr(tmp, 2);
	(*check)++;
}

void	ft_parse_params(t_data *data, int *gnl, char **line, int fd)
{
	int	i;
	int	check;

	*line = ft_calloc(1, 1);
	i = 0;
	check = 0;
	data->floor[0] = -1;
	data->ceilling[0] = -1;
	ft_gnl_read(data, gnl, fd, line);
	ft_check_write_params(data, line, &check);
	while (*gnl != 0 && check != 6)
	{
		ft_gnl_read(data, gnl, fd, line);
		ft_check_write_params(data, line, &check);
		i++;
	}
	if (check != 6)
	{
		free(*line);
		ft_error(data, "Not enough argumetns", 0);
	}
	ft_open_args(data, data->mlx);
}
