/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chasimir <chasimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 13:14:06 by scoach            #+#    #+#             */
/*   Updated: 2022/03/17 17:33:37 by chasimir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_free_all(int fd, char ***rest, int key)
{
	int	i;

	if (*rest != NULL && fd >= 0)
	{
		free((*rest)[fd]);
		(*rest)[fd] = NULL;
		i = 0;
		while (i < 1024 && ((*rest)[i] == NULL || (*rest)[i][0] == '\0'))
			i++;
		if (i == 1024)
		{
			while (i > 0)
			{
				i--;
				if ((*rest)[i] != NULL)
				{
					free((*rest)[i]);
					(*rest)[i] = NULL;
				}
			}
			free(*rest);
			*rest = NULL;
		}
	}
	return (key);
}

/*size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	while (i < count * size)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (start >= (unsigned int)ft_strlen(s))
		len = 0;
	if (len > ((size_t)(ft_strlen(s) - start)))
		len = (size_t)(ft_strlen(s) - start);
	i = 0;
	substr = malloc(sizeof(char const) * (len + 1));
	if (! substr)
		return (NULL);
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*strjoin;
	int		first_len;
	int		second_len;
	int		i;

	i = 0;
	first_len = ft_strlen(s1);
	second_len = ft_strlen(s2);
	strjoin = malloc(sizeof(char) * (first_len + second_len + 1));
	if (strjoin == NULL)
		return (NULL);
	while (i < first_len)
	{
		strjoin[i] = s1[i];
		i++;
	}
	while (i < (first_len + second_len))
	{
		strjoin[i] = s2[i - first_len];
		i++;
	}
	strjoin[i] = '\0';
	return (strjoin);
}*/
