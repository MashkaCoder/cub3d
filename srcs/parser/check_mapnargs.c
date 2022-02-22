/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mapnargs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoach <scoach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:11:41 by scoach            #+#    #+#             */
/*   Updated: 2022/02/22 18:45:13 by scoach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

// Референс, переделать
static void	ft_check_help(char **map, int *i, int *len, int *f_len)
{
	
}

// Референс, переделать
static void	ft_check_rectangularity_frame(char *map, int i, int len, int f_len)
{
	while (map[i] != '\n' && map[i] != '\0')
	{
		if (map[i] != '1' && map[i] != ' ')
			ft_error(data, "Frame is not full", 0);
		f_len++;
		i++;
	}
	ft_check_help(&map, &i, &len, &f_len);
	while (map[i - 1] != '\n' && i > 0)
	{
		i--;
		if (map[i] != '1' && map[i] != ' ')
			ft_error(data, "Frame is not full!", 0);
	}
}

static void ft_check_frame(char **map, int i, int len, int f_len)
{
	
}

// Референс, переделать
static void	ft_check_strangers_fullness(t_data *data, char *mp)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	while (mp[i] != '\0')
	{
		if (mp[i] != '0' && mp[i] != '1' && mp[i] != 'N' && mp[i] != 'S'
			&& mp[i] != 'E' && mp[i] != '\n' && mp[i] != 'W' && mp[i] != ' ')
		{
			mp[i + 1] = '\0';
			ft_error(data, ft_strjoin("Illegal character ", &(mp[i])), 0);
		}
		if (mp[i] == 'S' || mp[i] == 'N' || mp[i] == 'W' || mp[i] == 'E')
			p++;
		i++;
	}
	if (p < 1)
		ft_error(data, "Not enougth elements", 0);
	if (p > 1)
		ft_error(data, "Too many starting characters", 0);
}

void	ft_check_mapnargs(t_data *data)
{
	
}