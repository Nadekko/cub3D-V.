/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:15:39 by ede-cola          #+#    #+#             */
/*   Updated: 2025/02/17 13:17:04 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_data_start(t_data *data, char **file)
{
	if (mlx_start(data))
		return (ft_free_data(data), ft_free_tab(file),
			ft_putendl_fd("Error initalizing mlx failed", 2), 1);
	if (ft_check_textures(data) || ft_check_rgb(data))
		return (ft_free_data(data), ft_free_tab(file),
			ft_putendl_fd("Error invalid textures / image files", 2),
			1);
	else if (ft_check_map_closed(data->map->map_tab)
		|| ft_check_player(data->map->map_tab))
		return (ft_free_data(data), ft_free_tab(file),
			ft_putendl_fd("Error invalid map file", 2), 1);
	return (0);
}
