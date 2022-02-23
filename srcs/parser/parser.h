/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoach <scoach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:02:35 by scoach            #+#    #+#             */
/*   Updated: 2022/02/23 19:06:55 by scoach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

//Парсинг карты
void	ft_parse_params(t_data *data, int *gnl, char **line, int fd);
void	ft_check_map(t_data *data);
char	**ft_dd_parse(char *str_map);
void	ft_map_data_form(char **map, t_data *data, int i);

#endif
