/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoach <scoach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:02:35 by scoach            #+#    #+#             */
/*   Updated: 2022/03/18 16:18:17 by scoach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

//Парсинг карты
void	ft_parse_params(t_data *data, int *gnl, int fd);
void	ft_parse_rgb(t_data *data, char ***tmp, int *op, int i);
void	ft_check_map(t_data *data);

#endif
