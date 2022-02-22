/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoach <scoach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:56:05 by scoach            #+#    #+#             */
/*   Updated: 2022/02/22 21:22:25 by scoach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	ft_check_format(char *name)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	if (len > 254)
		ft_error(NULL, "Invalid filename: too many characters", 0);
	i = 0;
	while (name[i] != '\0')
	{
		if (name[i] == '/' || name[i] == '?' || name[i] == '<' || name[i] == '>'
			|| name[i] == '*' || name[i] == '"' || name[i] == '|')
			ft_error(NULL, "Invalid filename: illegal characters", 0);
		i++;
	}
	if (name[len - 4] != '.' || name[len - 3] != 'c' || name[len - 2] != 'u'
		|| name[len - 1] != 'b')
		ft_error(NULL, "Invalid format: file must have format \".cub\" ", 0);
}

t_data *ft_data_init(int fd)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		ft_error(data, "Data initialization", 0);
	ft_bzero(data, sizeof(data));
	data->map = ft_calloc(1, sizeof(char *));
	if (data->map == NULL)
		ft_error(data, "ft_calloc for map", 0);
	ft_parse_map(data, fd);
	if (data->map == NULL)
		ft_error(data, "Map didn't parsed or file is empty", 0);
	ft_check_mapnargs(data);
	return (data);
}

int	main(int argc, char *argv[])
{
	t_data	*data;
	int		fd;

	if (argc < 2)
		ft_error(NULL, "Too few arguments", 0);
	if (argc > 2)
		ft_error(NULL, "Too many arguments", 0);
	ft_check_format(argv[1]);
	fd = ft_open(argv[1]);
	data = ft_data_init(fd);
	if (close(fd) == -1)
	{
		ft_free_data(data);
		ft_error(data, ft_itoa(fd), 1);
	}
	ft_cub(data);
	exit(EXIT_SUCCESS);
}
