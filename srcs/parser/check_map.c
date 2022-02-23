/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoach <scoach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:11:41 by scoach            #+#    #+#             */
/*   Updated: 2022/02/23 18:42:31 by scoach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static void	ft_to_width(t_data *data, int y, int ln, int tmpln)
{
	char *tmp;
	char *tmp2;

	if (data->map[y][ln - 1] == '\n')
		ln--;
	if (data->map[y][ln] == '\n')
		data->map[y][ln] = '\0';
	if (ln < data->width)
	{
		tmpln = data->width - ln + 1;
		tmp2 = ft_strdup(data->map[y]);
		if (tmp2 == NULL)
			ft_error(data, "ft_to_width malloc", 0);
		tmp = ft_calloc(tmpln, sizeof(char));
		if (tmp == NULL)
			ft_error(data, "ft_to_width malloc", 0);
		tmpln--;
		tmp = ft_memset(tmp, ' ', tmpln - 1);
		free(data->map[y]);
		data->map[y] = ft_strjoin(tmp2, tmp);
		free(tmp);
		free(tmp2);
	}
	else
		data->width = ln;
}

static void	ft_check_core(t_data *data, char **m, int y, int x)
{
	while (m[y + 1] != NULL)
	{
		ft_to_width(data, y, ft_strlen(data->map[y]), 0);
		if (data->map[y] == NULL);
		{
			while(data->map[y + 1] != NULL)
			{
				free(data->map[y + 1]);
				y++;
			}
			ft_error(data, "malloc error ft_check_core", 0);
		}
		if ((m[y][0] != '1' && m[y][0] != ' ') 
			|| (m[y][data->width - 1] != '1' && m[y][data->width - 1] != ' '))
			ft_error(data, "Frame is not full!", 0);
		while (m[y][x + 1] != '\n' && m[y][x + 1] != '\0')
		{
			if ((m[y - 1][x] == ' ' || m[y + 1][x] == ' ' 
				|| m[y][x - 1] == ' ' || m[y][x + 1] == ' ') && m[y][x] != '1')
				ft_error(data, "Frame is not full!", 0);
			x++;
		}
		y++;
	}
	data->high = y;
}

static void	ft_check_rectangularity_frame(t_data *data, char **map, int i)
{
	while (map[0][data->width] != '\n' && map[0][data->width] != '\0')
	{
		if (map[0][data->width] != '1' && map[0][data->width] != ' ')
			ft_error(data, "Frame is not full", 0);
		data->width++;
	}
	if (data->map[1] != NULL)
	{
		ft_check_core(data, map, 1, 1);
		ft_to_width(data, data->high, ft_strlen(map[data->high]), 0);
		while (map[data->high - 1][i] != '\0')
		{
			if (map[data->high][i] != '1' && map[data->high - 1][i] != ' ')
				ft_error(data, "Frame is not full!", 0);
			i++;
		}
		data->high++;
	}
	i = 0;
	while (ft_strlen(map[i]) < data->width)
	{
		ft_to_width(data, i, ft_strlen(map[i]), 0);
		i++;
	}
}

static void	ft_check_strangers_fullness(t_data *data, char *m, int j)
{
	int i;
	int p;

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

void	ft_check_map(t_data *data)
{
	int i;
	
	i = 0;
	if (data->map == NULL)
		ft_error(data, "Map didn't parsed or file is empty", 0);
	while (data->map[i] != NULL)
	{
		ft_check_strangers_fullness(data, data->map[i], i);
		i++;
	}
	ft_check_rectangularity_frame(data, data->map, 0);
	if (data->map[0][data->width] == '\n')
		data->map[0][data->width] = '\0';
}