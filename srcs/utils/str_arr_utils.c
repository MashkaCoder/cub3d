/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoach <scoach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:44:14 by scoach            #+#    #+#             */
/*   Updated: 2022/02/21 18:59:00 by scoach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	ft_putarr_fd(char **arr, int fd)
{
	int	i;

	i = 0;
	ft_putchar_fd('\n', fd);
	if (arr != NULL)
	{
		while (arr[i] != NULL)
		{
			ft_putstr_fd(arr[i], fd);
			ft_putstr_fd(" ! ", fd);
			i++;
		}
		if (arr[i] == NULL)
			ft_putstr_fd("√", fd);
		ft_putchar_fd('\n', fd);
	}
}

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

char	**ft_arrdup(char **arr)
{
	char	**new_arr;
	int		i;

	i = 0;
	new_arr = malloc(sizeof(char *) * (ft_arrlen(arr) + 1));
	if (new_arr == NULL)
		return (NULL);
	while (arr[i] != NULL)
	{
		new_arr[i] = ft_strdup(arr[i]);
		if (new_arr[i] == NULL)
			return (ft_free_arr(new_arr, i));
		i++;
	}
	new_arr[i] = NULL;
	return (new_arr);
}

// Дополняет массив big с элемента bln значениями массива small 
int	ft_arr_to_arr(char ***big_arr, char **small_arr, int bln)
{
	int	i;

	i = 0;
	while (small_arr[i] != NULL)
	{
		(*big_arr)[i + bln] = ft_strdup(small_arr[i]);
		if ((*big_arr)[i + bln] == NULL)
			return (i);
		i++;
	}
	return (0);
}	

char	**ft_arrjoin(char **arr1, char **arr2)
{
	char	**final_arr;
	int		i;
	int		ln;
	int		sln;

	i = 0;
	if (arr1 == NULL || arr2 == NULL)
		return (NULL);
	sln = ft_arrlen(arr1);
	ln = sln + ft_arrlen(arr2) + 1;
	final_arr = malloc(sizeof(char *) * ln);
	if (final_arr == NULL)
		return (NULL);
	if (sln > 0)
		i = ft_arr_to_arr(&final_arr, arr1, 0);
	if (i)
		return (ft_free_arr(final_arr, i));
	if (ln - sln != 1)
		i = ft_arr_to_arr(&final_arr, arr2, sln);
	if (i)
		return (ft_free_arr(final_arr, i));
	final_arr[ln - 1] = NULL;
	return (final_arr);
}

static char	**ft_strtoarr(char *str)
{
	char	**arr;

	arr = malloc(sizeof(char *) * 2);
	if (arr == NULL)
		return (NULL);
	arr[0] = ft_strdup(str);
	if (arr[0] == NULL)
		return (ft_free_arr(arr, 0));
	arr[1] = NULL;
	return (arr);
}

char	**ft_arr_plus_one(char ***sub_arr, char *str, int i, int ln)
{
	char	**tmp;
	char	**tmp2;
	char	*substr;

	if (ln <= 0)
		return (*sub_arr);
	tmp = ft_arrdup(*sub_arr);
	ft_free_arr(*sub_arr, ft_arrlen(*sub_arr));
	if (tmp == NULL)
		return (NULL);
	substr = ft_substr(str, i, ln);
	if (substr == NULL)
		return (ft_free_arr(tmp, ft_arrlen(tmp)));
	tmp2 = ft_strtoarr(substr);
	free(substr);
	if (tmp2 == NULL)
		return (ft_free_arr(tmp, ft_arrlen(tmp)));
	(*sub_arr) = ft_arrjoin(tmp, tmp2);
	ft_free_arr(tmp, ft_arrlen(tmp));
	ft_free_arr(tmp2, ft_arrlen(tmp2));
	if (*sub_arr == NULL)
		return (NULL);
	return (*sub_arr);
}
