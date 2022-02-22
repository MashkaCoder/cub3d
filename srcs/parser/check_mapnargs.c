/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mapnargs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoach <scoach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:11:41 by scoach            #+#    #+#             */
/*   Updated: 2022/02/22 23:18:49 by scoach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void	ft_check_help(t_data *data, char **map)
{
	
}

static void	ft_check_rectangularity_frame(t_data *data, char **map)
{
	int	i;

	i = 0;
	while (map[0][i] != '\n' && map[0][i] != '\0')
	{
		if (map[0][i] != '1' && map[0][i] != ' ')
			ft_error(data, "Frame is not full", 0);
		data->width++;
		i++;
	}
	data->high++;
	ft_check_core(data, map);
	i = 0;
	while (map[data->high - 1][i] != '\n' && map[data->high - 1][i] != '\0')
	{
		if (map[data->high - 1][i] != '1' && map[data->high - 1][i] != ' ')
			ft_error(data, "Frame is not full!", 0);
		i++;
	}
}

static void	ft_check_strangers_fullness(t_data *data, char *m, int j)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	while (m[i] != '\0')
	{
		if (m[i] != '0' && m[i] != '1' && m[i] != 'N' && m[i] != 'S'
			&& m[i] != 'E' && m[i] != '\n' && m[i] != 'W' && m[i] != ' ')
		{
			m[i + 1] = '\0';
			ft_error(data, ft_strjoin("Illegal character ", &(m[i])), 0);
		}
		if (m[i] == 'S' || m[i] == 'N' || m[i] == 'W' || m[i] == 'E')
		{
			p++;
			data->player_base[0] = i;
			data->player_base[1] = j;
		}
		i++;
	}
	if (p < 1)
		ft_error(data, "Where is starting character?", 0);
	if (p > 1)
		ft_error(data, "Too many starting characters", 0);
}

void	ft_check_mapnargs(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[i] != NULL)
	{
		ft_check_strangers_fullness(data, data->map[i], i);
		i++;
	}
	ft_check_rectangularity_frame(data, data->map);
	ft_open_args(data);
}