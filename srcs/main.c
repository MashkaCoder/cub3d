/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoach <scoach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:56:05 by scoach            #+#    #+#             */
/*   Updated: 2022/03/05 13:42:52 by scoach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	ft_parse_map(t_data *data, int fd)
{
	int		gnl;
	int		l;
	char	*ln;

	ln = ft_calloc(1, 1);
	ft_parse_params(data, &gnl, &ln, fd);
	ft_gnl_read(data, &gnl, fd, &ln);
	while (gnl != 0 && ln[0] == '\0')
		ft_gnl_read(data, &gnl, fd, &ln);
	while (gnl != 0)
	{
		l = ft_strlen(ln);
		if (l > data->width)
			data->width = l; 
		if (ln[0] == '\0' || ft_arr_plus_one(&(data->map), ln, 0, l) == NULL)
		{
			free(ln);
			ft_error(data, "map divided", 0);
		}
		ft_gnl_read(data, &gnl, fd, &ln);
	}
	if (ft_arr_plus_one(&(data->map), ln, 0, ft_strlen(ln)) == NULL)
		ft_error(data, "last string of map did't parsed", 0);
	free(ln);
}

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
		if (name[i] == '?' || name[i] == '<' || name[i] == '>'
			|| name[i] == '*' || name[i] == '"' || name[i] == '|')
			ft_error(NULL, "Invalid filename: illegal characters", 0);
		i++;
	}
	if (name[len - 4] != '.' || name[len - 3] != 'c' || name[len - 2] != 'u'
		|| name[len - 1] != 'b')
		ft_error(NULL, "Invalid format: file must have format \".cub\" ", 0);
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
	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		ft_error(data, "Data initialization", 0);
	ft_bzero(data, sizeof(t_data));
	data->map = ft_calloc(1, sizeof(char *));
	if (data->map == NULL)
		ft_error(data, "ft_calloc for map", 0);
	ft_parse_map(data, fd);
	if (close(fd) == -1)
		ft_error(data, ft_itoa(fd), 1);
	data->high = ft_arrlen(data->map);
	ft_check_map(data);
	ft_putarr_fd(data->map, 1);
	//ft_cub(data);
	ft_free_data(data);
	system("leaks a.out");
	exit(EXIT_SUCCESS);
}