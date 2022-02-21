/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_arr_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoach <scoach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:20:45 by scoach            #+#    #+#             */
/*   Updated: 2022/02/16 18:40:55 by scoach           ###   ########.fr       */
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

char	**ft_strtoarr(char *str)
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

/*
	Функция вытаскивает нуль-терменированную подстроку
	из нуль-терменированной строки.

	Принимаемые аргументы:

		1) char	*str - изначальная строка;
		2) int	start - номер символа, с которого ачинается подстрока;
		3) int	ln - длина подстроки.

	Возвращаемое значение:

		char *prt - нуль-терменированная строка.
*/
char	*ft_strprt(char *str, int start, int ln)
{
	char	*prt;
	int		i;

	prt = malloc(sizeof(char) * (ln + 1));
	if (prt == NULL)
		return (NULL);
	prt[ln] = '\0';
	i = 0;
	while (i < ln)
	{
		prt[i] = str[start + i];
		i++;
	}
	return (prt);
}

/*
	Удаляет символ из строки

	Принимаемые аргументы:

		1) char		**s - указатель на изначальную строку;
		2) char		*a - номер символа, который требуется удалить;

	Возвращаемое значение:

		int - проверочное значение. 0 в случае ОШИБКИ!!!
*/
int	ft_remove_symb(char **str, int num)
{
	char	*tmp;
	int		i;

	tmp = ft_strdup(*str);
	if (tmp == NULL)
		return (-1);
	free(*str);
	i = ft_strlen(tmp);
	if (i == 0)
		i++;
	*str = malloc(sizeof(char) * (i));
	i = 0;
	if (*str != NULL)
	{
		while (i < num)
		{
			(*str)[i] = tmp[i];
			i++;
		}
		while (tmp[i + 1] != '\0')
		{
			(*str)[i] = tmp[i + 1];
			i++;
		}
		(*str)[i] = '\0';
	}
	free(tmp);
	return (i);
}
