/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:39:19 by andjenna          #+#    #+#             */
/*   Updated: 2025/02/22 20:52:21 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_bonus.h"

// void	draw_player(t_data *data)
// {
// 	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
// 		data->mlx->img[2]->img, data->player->pos_x * (PIXEL),
// 		data->player->pos_y * (PIXEL));
// }

// void	draw_ray2(t_data *data, double ray_x, double ray_y, double dir_x,
//     double dir_y)
// {
// int	map_x;
// int	map_y;

//     while (1)
//     {
//         map_x = (int)ray_x;
//         map_y = (int)ray_y;
//         if (map_x < 0 || map_x >= data->map->width || map_y < 0
//             || map_y >= data->map->height)
//             break ;
//         if (data->map->map_int[map_y][map_x] == 1)
//             break ;
//         mlx_pixel_put(data->mlx->mlx, data->mlx->win, (ray_x * PIXEL) 
//				+ (PIXEL
//                 / (PIXEL / 2)), (ray_y * PIXEL) + (PIXEL / (PIXEL / 2)),
//             0x00FF00);
//         // Avancer petit à petit dans la direction du rayon
//         ray_x += dir_x * 0.1;
//         ray_y += dir_y * 0.1;
//     }
// }
// void	draw_floor(t_data *data)
// {
// 	int	x;
// 	int	y;

// 	x = 0;
// 	y = 0;
// 	while (data->map->map_tab[y] && y < data->map->height)
// 	{
// 		while (data->map->map_tab[y][x] && x < data->map->width)
// 		{
// 			if ((data->map->map_int[y][x] == 0 || data->map->map_int[y][x] == 3)
// 				&& data->map->map_int[y][x] != 1
// 				&& data->map->map_int[y][x] != 2)
// 				mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
// 					data->mlx->img[0]->img, x * (PIXEL), y * (PIXEL));
// 			x++;
// 		}
// 		x = 0;
// 		y++;
// 	}
// }
// void	draw_wall(t_data *data)
// {
// 	int	x;
// 	int	y;

// 	x = 0;
// 	y = 0;
// 	while (data->map->map_tab[y] && y < data->map->height)
// 	{
// 		while (data->map->map_tab[y][x] && x < data->map->width)
// 		{
// 			if (data->map->map_int[y][x] == 1)
// 				mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
// 					data->mlx->img[1]->img, x * (PIXEL), y * (PIXEL));
// 			x++;
// 		}
// 		x = 0;
// 		y++;
// 	}
// }
