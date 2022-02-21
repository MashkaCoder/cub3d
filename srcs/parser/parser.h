/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoach <scoach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:02:35 by scoach            #+#    #+#             */
/*   Updated: 2022/02/21 17:12:37 by scoach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

//Парсинг карты
void	ft_parse_map(t_data *data, int fd);
char	**ft_dd_parse(char *str_map);
void	ft_map_data_form(char **map, t_data *data, int i);

//Функции для работы с массивом
char	**ft_arr_plus_one(char ***sub_arr, char *str, int i, int ln);

#endif
