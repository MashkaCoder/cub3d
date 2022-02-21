/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoach <scoach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:44:14 by scoach            #+#    #+#             */
/*   Updated: 2022/02/21 18:47:35 by scoach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
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
