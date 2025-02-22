/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:10:59 by andjenna          #+#    #+#             */
/*   Updated: 2025/02/22 18:15:21 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

void	draw_player_to_image(t_data *data)
{
	put_img_to_img(data, *data->mlx->img[4], 0, 0);
}

// void	set_texture(t_data *data)
// {
// 	double wall_x;

// 	if (data->raycast->side == 0)
// 		wall_x = data->player->pos_y + data->raycast->wall_dist
// 			* data->raycast->ray_y;
// 	else
// 		wall_x = data->player->pos_x + data->raycast->wall_dist
// 			* data->raycast->ray_x;
// 	wall_x -= floor(wall_x);
// 	if (data->raycast->side == 0)
// 	{
// 		if (data->raycast->ray_x > 0)
// 			data->raycast->texture = NO_TEXTURE;
// 		else
// 			data->raycast->texture = SO_TEXTURE;
// 	}
// 	else
// 	{
// 		if (data->raycast->ray_y > 0)
// 			data->raycast->texture = EA_TEXTURE;
// 		else
// 			data->raycast->texture = WE_TEXTURE;
// 	}
// 	int	tex_x = (int)(wall_x * (double)PIXEL);
// 	if ((data->raycast->side == 0 && data->raycast->ray_x > 0) || (data->raycast->side == 1 && data->raycast->ray_y < 0))
// 		tex_x = PIXEL - tex_x - 1;
// 	int	y;
// 	int	color;
// 	int	tex_y;

// 	y = data->raycast->draw_start;
// 	while (y < data->raycast->draw_end)
// 	{
// 		tex_y = (y - data->raycast->draw_start) * PIXEL / data->raycast->line_height;
// 		color = get_pixel(*data->mlx->img[data->raycast->texture], tex_x, tex_y);
// 		put_pixel(data->mlx->img[5], data->raycast->draw_start, y, color);
// 		y++;
// 	}
// }
// // void	draw_texture(t_data *data)
// // {
	
// // }

// void	draw_wall_to_image(t_data *data, int x, int draw_start, int draw_end)
// {
// 	int	y;
// 	int	color;

// 	if (data->raycast->side == 0)
// 		color = 0xaf70d1;
// 	else
// 		color = 0x48225d;
// 	y = draw_start;
// 	while (y < draw_end)
// 	{
// 		put_pixel(data->mlx->img[5], x, y, color);
// 		y++;
// 	}
// 	set_texture(data);
// }
