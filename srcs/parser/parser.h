/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoach <scoach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:02:35 by scoach            #+#    #+#             */
/*   Updated: 2022/03/04 21:35:04 by scoach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

//Парсинг карты
void	ft_parse_params(t_data *data, int *gnl, char **line, int fd);
void	ft_parse_rgb(t_data *data, char ***tmp, int (*op)[3], int i);
void 	ft_open_args(t_data *data, void *mlx);
void	ft_destroy_images(t_data *data);
void	ft_check_map(t_data *data);
char	**ft_dd_parse(char *str_map);
void	ft_map_data_form(char **map, t_data *data, int i);

#endif
