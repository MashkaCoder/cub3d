/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoach <scoach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 20:49:59 by scoach            #+#    #+#             */
/*   Updated: 2022/02/21 19:42:21 by scoach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	ft_map_data_form(char **map, t_data *data, int i)
{
	
	data->width = ft_strlen(map[0]);
	data->high = 0;
	while (map[data->high] != NULL)
	{
		i = 0;
		while (map[data->high][i] != '\0')
		{
			if (map[data->high][i] == 'P')
			{
				data->player_base[1] = i;
				data->player_base[0] = data->high;
			}
			i++;
		}
		data->high++;
	}
}

static char	**ft_dd_parse_continue(char *str_map, char ***map, int len)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str_map[i] != '\0')
	{
		if (str_map[i] == '\n')
			(*map)[count][i - len * count] = '\0', count++;
		else
			(*map)[count][i - len * count] = str_map[i];
		i++;
	}
	(*map)[count][i - len * count] = '\0';
	return (*map);
}

char	**ft_dd_parse(char *str_map)
{
	char	**map;
	int		i;
	int		count;
	int		len;

	i = 0;
	len = 0;
	count = 1;
	while (str_map[i] != '\0')
	{
		if (str_map[i] == '\n')
			count++, len = 0;
		len++;
		i++;
	}
	map = (char **)malloc(sizeof(char *) * (count + 1));
	map[count] = NULL;
	while (count > 0)
	{
		count--; 
		map[count] = (char *)malloc(sizeof(char) * (len + 1));
	}
	return (ft_dd_parse_continue(str_map, &map, len));
}

void	ft_parse_map(t_data *data, int fd)
{
	int		gnl;
	char	*ln;

	ln = ft_calloc(1, 1);
	ft_parse_params(data, &gnl, &ln, fd);
	while (gnl != 0 && ln[0] == '\n')
		ft_gnl_read(data, &gnl, fd, &ln);
	while (gnl != 0)
	{
		if ((ln[0] != '\n')
			&& (ft_arr_plus_one(&(data->map), ln, 0, ft_strlen(ln)) == NULL))
			ft_error(data, "Realy shitty shit", 0);
		//else Надо узнать, нужно ли прерываться в этом случае
		ft_gnl_read(data, &gnl, fd, &ln);
	}
	free(ln);
}