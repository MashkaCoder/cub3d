#include "cub.h"

int	ft_free_arr(char **arr, int ln)
{
	int i;

	if (arr != NULL)
	{
		i = 0;
		while (i < ln)
		{
			if (arr[i] != NULL)
			{
				ft_bzero(arr[i], ft_strlen(arr[i]));
				free(arr[i]);
			}
			i++;
		}
		ft_bzero(arr, sizeof(char *));
		free(arr);
	}
}



void	ft_free_data(t_data *data)
{
	int	i;

	if (data != NULL)
	{
		if (data->map != NULL)
			ft_free_arr(data->map, ft_arrlen(data->map));
		i = 0;
		while (i < 4)
		{
			if (data->nswe[i] != NULL)
				free(data->nswe);
			i++;
		}
		ft_bzero(data->nswe, sizeof(char *) * 4);
		ft_bzero(data, sizeof(t_data));
		free(data);
	}
}
