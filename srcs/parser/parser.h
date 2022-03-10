/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chasimir <chasimir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:02:35 by scoach            #+#    #+#             */
/*   Updated: 2022/03/08 22:00:18 by chasimir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

//Парсинг карты
void	ft_parse_params(t_data *data, int *gnl, int fd);
void	ft_parse_rgb(t_data *data, char ***tmp, int *op, int i);
// void	ft_open_args(t_data *data, void *mlx);
void	ft_open_args(t_data *data, t_raycast *raycast); //  у тебя 2-ым парам был mlx
void	ft_destroy_images(t_data *data);
void	ft_check_map(t_data *data);
char	**ft_dd_parse(char *str_map);
void	ft_map_data_form(char **map, t_data *data, int i);

#endif
