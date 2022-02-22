/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoach <scoach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 19:09:19 by scoach            #+#    #+#             */
/*   Updated: 2022/02/21 19:30:53 by scoach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	ft_error(t_data *data, char *msg, int op)
{
	ft_putstr_fd("Error\n", 2);
	if (op == 0)
		ft_putstr_fd(msg, 2);
	if (op == 1)
		perror(msg);
	ft_free_data(data);
	exit(EXIT_FAILURE);
}

int	ft_open(char *flnm)
{
	int	fd;

	fd = open(flnm, O_RDONLY);
	if (fd == -1)
		ft_error(NULL, flnm, 1);
	return (fd);
}

void	ft_gnl_read(t_data *data, int *gnl, int fd, char **ln)
{
	*gnl = ft_get_next_line(fd, ln);
	if (*gnl == -1)
	{
		if (close(fd) == -1)
			ft_error(data, "GNL and close", 0);
		ft_error(data, "GNL", 0);
	}
}
